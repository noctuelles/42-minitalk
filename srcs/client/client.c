/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:44:29 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/22 03:08:46 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "minitalk_client.h"

#include <unistd.h>

t_client	client;

void	handler(int signum)
{
	if (signum == SIGUSR1)
		client.flags |= PONG_OK;
	else if (signum == SIGUSR2)
		client.flags |= MSG_ACK;
}

int	send_bit(uint64_t val)
{
	if (val)
	{
		//write(1, "1", 1);
		if (kill(client.srv_pid, SIGUSR1) == -1)
			return (CODE_INVALID_PID);
	}
	else
	{
		//write(1, "0", 1);
		if (kill(client.srv_pid, SIGUSR2) == -1)
			return (CODE_INVALID_PID);
	}
}

int	send_data(uint64_t data, size_t size)
{
	size_t	i;

	i = size * 8;
	while (i)
	{
		client.flags &= ~PONG_OK;
		if (send_bit(data & (1ULL << (i - 1))) == -1)
			return (CODE_INVALID_PID);
		usleep(500);
		if (!(client.flags & PONG_OK))
			return (CODE_SRV_TIMEOUT);
		i--;
	}
	//write(1, "\n", 1);
	return (0);
}

int	send_string(const char *str)
{
	size_t	i;
	int		ret;

	i = 0;
	while (str[i] != '\0')
	{
		ret = send_data(str[i], sizeof(unsigned char));
		if (ret != 0)
			return (ret);
		i++;
	}
	return (0);
}

int	send_message()
{
	int	ret;

	ret = send_data(client.msg_len, sizeof(size_t));
	if (ret != 0)
		return (ret);
	usleep(200);
	ret = send_string(client.msg);
	if (ret != 0)
		return (ret);
	return (0);
}

int	set_sigaction()
{
	struct sigaction	sigact;

	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigact.sa_handler = &handler;
	if (sigaction(SIGUSR1, &sigact, NULL) == -1)
		return (-1);
	if (sigaction(SIGUSR2, &sigact, NULL) == -1)
		return (-1);
	return (0);
}

int raise_error(int errcode)
{
	if (errcode == 1)
		ft_printf(FATAL ARGC_1);
	else if (errcode == 2)
		ft_printf(FATAL ARGC_2);
	else if (errcode == CODE_INVALID_PID)
		ft_printf(FATAL INVALID_PID);
	else if (errcode == CODE_SIGACT_FAIL)
		ft_printf(FATAL SETUP_SIGACT_ERROR);
	else if (errcode == CODE_SRV_TIMEOUT)
		ft_printf(FATAL TIMEOUT);
	else if (errcode == CODE_BAD_ACK)
		ft_printf(FATAL BAD_ACK);
	return (errcode);
}

int	main(int argc, char **argv)
{
	int	msg_err;

	if (argc < 3)
		return (raise_error(argc));
	if (set_sigaction() == -1)
		return (raise_error(CODE_SIGACT_FAIL));
	client.msg = argv[2];
	client.flags = 0;
	client.msg_len = ft_strlen(argv[2]);
	client.srv_pid = ft_atoi(argv[1]);
	msg_err = send_message();
	if (msg_err != 0)
		return (raise_error(msg_err));
	if (!(client.flags & MSG_ACK))
		return (raise_error(CODE_BAD_ACK));
	else
		ft_printf(SUCESS SMSG_ACK, client.srv_pid);
	return (0);
}

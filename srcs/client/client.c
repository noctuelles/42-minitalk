/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:44:29 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/23 05:57:45 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_client.h"
#include "ft_printf.h"
#include <unistd.h>

t_client	g_client;

void	handler(int signum)
{
	if (signum == SIGUSR1)
		g_client.flags |= PONG_OK;
	else if (signum == SIGUSR2)
		g_client.flags |= MSG_ACK;
}

int	set_sigaction(void)
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

int	main(int argc, char **argv)
{
	int	msg_err;

	if (argc < 3)
		return (raise_error(argc));
	g_client.msg = argv[2];
	g_client.flags = 0;
	g_client.msg_len = ft_strlen(argv[2]);
	g_client.srv_pid = ft_atoi(argv[1]);
	if (set_sigaction() == -1)
		return (raise_error(CODE_SIGACT_FAIL));
	if (g_client.srv_pid == 0)
		return (raise_error(CODE_INVALID_PID));
	msg_err = send_message();
	if (msg_err != 0)
		return (raise_error(msg_err));
	usleep(500);
	if (!(g_client.flags & MSG_ACK))
		return (raise_error(CODE_BAD_ACK));
	else
		ft_printf(SUCESS SMSG_ACK, g_client.srv_pid);
	return (0);
}

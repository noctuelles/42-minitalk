/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 05:32:06 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/05 17:45:17 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_client.h"
#include "ft_printf.h"
#include <unistd.h>

static int	send_bit(uint64_t val)
{
	if (val)
	{
		if (kill(g_client.srv_pid, SIGUSR1) == -1)
			return (CODE_INVALID_PID);
	}
	else
	{
		if (kill(g_client.srv_pid, SIGUSR2) == -1)
			return (CODE_INVALID_PID);
	}
	return (0);
}

static int	send_data(uint64_t data, size_t size)
{
	size_t	i;

	i = size * 8;
	while (i)
	{
		g_client.flags &= ~PONG_OK;
		if (send_bit(data & (1ULL << (i - 1))) == -1)
			return (CODE_INVALID_PID);
		usleep(TIMEOUT_US);
		if (!(g_client.flags & PONG_OK))
			return (CODE_SRV_TIMEOUT);
		i--;
	}
	return (0);
}

static int	send_string(const char *str)
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

int	raise_error(int errcode)
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
	else if (errcode == CODE_EMPTY_STR)
		ft_printf(FATAL EMPTY_STR);
	return (errcode);
}

int	send_message(void)
{
	int	ret;

	ret = send_data(g_client.msg_len, sizeof(size_t));
	if (ret != 0)
		return (ret);
	usleep(30);
	ret = send_string(g_client.msg);
	if (ret != 0)
		return (ret);
	return (0);
}

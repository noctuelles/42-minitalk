/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:18:08 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/24 01:45:37 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_server.h"
#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

void	prepare_new_msg(void)
{
	ft_memset(&g_server, 0, sizeof(t_server));
	g_server.offset = 63;
	ft_printf(LISTEN);
	pause();
}

int	await_reception(t_server_flags flag)
{
	while (!(g_server.flags & flag))
	{
		usleep(200);
		if (kill(g_server.clt_pid, SIGUSR1) == -1)
			return (-1);
	}
	return (0);
}

void	putmsg(void)
{
	ft_putstr(S_0 S_1);
	ft_printf(MSG, g_server.clt_pid, g_server.msg);
	ft_printf("Message size : %u\n", g_server.msg_len);
	ft_putstr(S_0 S_1);
	free(g_server.msg);
}

int	raise_error(int errcode)
{
	if (errcode == CODE_SIGACT_FAIL)
		ft_printf(FATAL SETUP_SIGACT_ERROR);
	else if (errcode == CODE_PONG_FAIL)
		ft_printf(FATAL ACK_SIGNAL_ERROR);
	else if (errcode == CODE_MALLOC_FAIL)
		ft_printf(FATAL MALLOC_FAIL);
	free(g_server.msg);
	return (errcode);
}

void	handle_interrupt(int signum)
{
	(void) signum;
	ft_printf("\n{1}Goodbye...{0}\n");
	free(g_server.msg);
	exit(1);
}

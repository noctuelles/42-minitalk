/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:28:55 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/24 01:46:34 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_server.h"
#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>

t_server	g_server;

void	receive_msg_size(int signum)
{
	if (signum == SIGUSR1)
		g_server.msg_len |= (1ULL << g_server.offset);
	if (g_server.offset == 0)
	{
		g_server.offset = 7;
		g_server.flags |= MALLOC;
	}
	else
		g_server.offset--;
}

void	receive_msg(int signum)
{
	if (signum == SIGUSR1)
		g_server.mchar |= (1U << g_server.offset);
	if (g_server.offset == 0)
	{
		g_server.msg[g_server.msg_i++] = g_server.mchar;
		g_server.mchar = 0;
		g_server.offset = 7;
		if (g_server.msg_i == g_server.msg_len)
		{
			g_server.msg[g_server.msg_i] = '\0';
			g_server.flags |= MSG_OK;
		}
	}
	else
		g_server.offset--;
}

void	handler(int signum, siginfo_t *siginfo, void *ucontext)
{
	(void) ucontext;
	g_server.clt_pid = siginfo->si_pid;
	if (!(g_server.flags & MALLOC))
		receive_msg_size(signum);
	else
		receive_msg(signum);
}

int	set_sigaction(void)
{
	struct sigaction	sigact;

	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = SA_SIGINFO;
	sigact.sa_sigaction = &handler;
	if (sigaction(SIGUSR1, &sigact, NULL) == -1)
		return (-1);
	if (sigaction(SIGUSR2, &sigact, NULL) == -1)
		return (-1);
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigact.sa_sigaction = NULL;
	sigact.sa_handler = &handle_interrupt;
	if (sigaction(SIGINT, &sigact, NULL) == -1)
		return (-1);
	ft_putstr(CLR_SCREEN);
	ft_printf("{33}" W_0 W_1 W_2 W_3 W_4 "{0}" HI S_0 S_1, getpid());
	return (0);
}

int	main(void)
{
	if (set_sigaction() == -1)
		return (raise_error(CODE_SIGACT_FAIL));
	while (1)
	{
		prepare_new_msg();
		if (await_reception(MALLOC) == -1)
			return (raise_error(CODE_PONG_FAIL));
		g_server.msg = malloc((g_server.msg_len + 1) * sizeof(char));
		if (!g_server.msg)
			return (raise_error(CODE_MALLOC_FAIL));
		if (await_reception(MSG_OK) == -1)
			return (raise_error(CODE_PONG_FAIL));
		if (kill(g_server.clt_pid, SIGUSR2) == -1)
			return (raise_error(CODE_PONG_FAIL));
		putmsg();
	}
	return (0);
}

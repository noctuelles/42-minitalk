/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:28:55 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/21 15:31:14 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "ft_printf.h"
#include <unistd.h>

t_server	server = 
{
	.msg = NULL,
	.mchar = 0,
	.msg_len = 0,
	.msg_i = 0,
	.flags = 0,
	.offset = 63,
	.clt_pid = 0
};

void	receive_msg_size()
{
	if (signum == SIGUSR1)
		server.msg_len |= (1ULL << server.offset);
	if (server.offset == 0)
	{
		server.offset = 7;
		server.flags |= MALLOC;
	}
	else
		server.offset--;
}

void	receive_msg()
{
	if (signum == SIGUSR1)
		server.mchar |= (1U << server.offset); 
	if (server.offset == 0)
	{
		server.msg[server.msg_i++] = server.mchar;
		if (server.msg_len == (server.msg_i + 1))
		{
			server.msg[server.msg_i] = '\0';
			server.flags |= MSG_OK;
		}
		else
			server.offset = 7;
	}
	else
		server.offset--;
}

void	handler(int signum, siginfo_t *siginfo, void *ucontext)
{
	if (!server.clt_pid)
		server.clt_pid = siginfo->si_pid;
	if (!is_flag_set(MALLOC))
		receive_msg_size(signum);
	if (!is_flag_set(MSG_OK))
		receive_msg(signum);
	if (kill(server.clt_pid, signum) == -1)
		server.flags |= ERR;
}

int	set_sigaction()
{
	struct sigaction	sigact;

	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = SA_SIGINFO;
	sigact.sa_sigaction = &handler;
	if (sigaction(SIGUSR1, &sigact, NULL) == -1)
		return (-1);
	if (sigaction(SIGUSR2, &sigact, NULL) == -1)
		return (-1);
	ft_printf("{33;5}" WLC "{0}" HI S, getpid());
}

int	main(void)
{
	if (!set_sigaction())
		return (raise_error(CODE_SIGACT_FAIL));
	while (1)
	{
		prepare_new_msg();
		if (await_reception(MALLOC) == -1)
			return (raise_error(CODE_PONG_FAIL));
		server.msg = malloc((server.msg_len + 1) * sizeof(char));
		if (!server.msg)
			return (raise_error(CODE_MALLOC_FAIL));
		if (await_reception(MSG_OK) == -1)
			return (raise_error(CODE_PONG_FAIL));
		putmsg();
	}
	return (0);
}

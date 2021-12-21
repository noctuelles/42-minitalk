/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:18:08 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/21 15:31:15 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	prepare_new_msg()
{
	ft_memset(&server, 0, sizeof(t_server));
	server.offset = 63;
	ft_printf(LISTEN);
}

unsigned int	is_flag_set(t_server_flags flag)
{
	if (server.flags & flag)
		return (1);
	return (0);
}

int	await_reception(t_server_flags flag)
{
	while (is_flag_set(flag) && !is_flag_set(ERR))
		pause();
	if (server.flags & ERR)
		return (-1);
	return (0);
}

void	putmsg()
{
	ft_printf(MSG, server.clt_pid, server.msg);
	free(server.msg);
}

int	raise_error(int errcode)
{
	if (errcode == CODE_SIGACT_FAIL)
		ft_printf(FATAL SETUP_SIGACT_SETUP);
	else if (errcode == CODE_PONG_FAIL)
		ft_printf(FATAL ACK_SIGNAL_ERROR);
	else if (errcode == CODE_MALLOC_FAIL)
		ft_printf(FATAL MALLOC_FAIL);
	return (errcode);
}



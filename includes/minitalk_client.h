/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_client.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:31:36 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/05 17:44:40 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_CLIENT_H
# define MINITALK_CLIENT_H

# include <stdint.h>
# include <signal.h>

# define FATAL "{31;1}[FATAL]{0} : "
# define SUCESS "{32;1}[SUCESS]{0} : "

# define INVALID_PID "Unable to send message : the PID might be invalid.\n"
# define TIMEOUT "Server time-out, your system might be too slow.\n"
# define SETUP_SIGACT_ERROR "Unable to setup signal action.\n"
# define EMPTY_STR "The string you're trying to send is empty... not wasting my time!\n"
# define ARGC_1 "No P.I.D and message specified.\n"
# define ARGC_2 "No P.I.D or message specified.\n"
# define SMSG_ACK "The message has been delivered to the server [{31}%u{0}] !\n"
# define BAD_ACK "The message hasn't been delivered to the server.\n"

# define CODE_INVALID_PID -1
# define CODE_SIGACT_FAIL -2
# define CODE_SRV_TIMEOUT -3
# define CODE_BAD_ACK -4
# define CODE_EMPTY_STR -5

# define TIMEOUT_US 2000

typedef struct s_minitalk_client
{
	const char	*msg;
	size_t		msg_len;
	pid_t		srv_pid;
	uint8_t		flags;
}				t_client;

enum e_client_flags
{
	MSG_ACK=0x01,
	PONG_OK=0x02
};

extern t_client	g_client;

int	raise_error(int errcode);
int	send_message(void);

#endif

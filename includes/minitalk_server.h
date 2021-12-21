/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_server.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:33:00 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/21 15:33:17 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_SERVER_H
#define MINITALK_SERVER_H

# include <signal.h>
# include <stdint.h>

# define FATAL "{31;1}[FATAL]{0} : "
# define SEND_ERROR_PID "Unable to send message : the P.I.D might be invalid.\n"
# define SEND_ERROR_SRV "Unable to send message : the server may me down.\n"
# define SETUP_SIGACT_ERROR "Unable to setup signal action.\n"
# define ACK_SIGNAL_ERROR "Unable to pong back client; did you kill it ?\n"
# define MSG_RECEIVED "Message received from [%u]\n\n\t%s\n\n"
# define MALLOC_FAIL "Could not allocate memory.\n"

# define CODE_SIGACT_FAIL -1
# define CODE_PONG_FAIL -2
# define CODE_MALLOC_FAIL -3

# define S_0 "-----------------------------------"
# define S_1 "-----------------------------------\n\n"
# define S S_0 S_1

# define W_0 "\n███    ███ ██ ███    ██ ██ ████████  █████  ██      ██   ██\n"
# define W_1 "████  ████ ██ ████   ██ ██    ██    ██   ██ ██      ██  ██ \n"
# define W_2 "██ ████ ██ ██ ██ ██  ██ ██    ██    ███████ ██      █████  \n" 
# define W_3 "██  ██  ██ ██ ██  ██ ██ ██    ██    ██   ██ ██      ██  ██ \n" 
# define W_4 "██      ██ ██ ██   ████ ██    ██    ██   ██ ███████ ██   ██\n\n"
# define WLC W_0 W_1 W_2 W_3 W_4

# define HI "{4}Hello.. feel free to send me messages at :{0} [{31}%u{0}] :)\n"
# define LISTEN "{3;1}Listening...{0}\n"
# define MSG "\n\t{4}Message received from{0} [{31}%u{0}] :\n\n\"%s\"\n"

typedef enum e_server_flags
{
	MALLOC=0x01,
	MSG_OK=0x02,
	CLIENT_ERR=0x04
}				t_server_flags;

typedef struct s_minitalk_server
{
	char	*msg;
	char	mchar;
	size_t	msg_len;
	size_t	msg_i;
	uint8_t	flags;
	size_t	offset;
	pid_t	clt_pid;
}				t_server;

extern t_server server;

#endif

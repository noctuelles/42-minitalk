/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 21:37:05 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/20 22:28:51 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
#define MINITALK_H

# include <signal.h>

# define SEND_ERROR_PID "Unable to send message : the P.I.D might be invalid.\n"
# define SEND_ERROR_SRV "Unable to send message : the server may me down.\n"
# define SETUP_SIGACT_ERROR "Unable to setup signal action.\n"
# define ACK_SIGNAL_ERROR "Unable to ping back client; did you kill it ?\n"
# define MSG_RECEIVED "Message received from [%u]\n\n\t%s\n\n"

# define RED "\x1b[31m"
# define RST "\x1b[0m"
# define UDL "\x1b[4m"
# define S_0 "-----------------------------------"
# define S_1 "-----------------------------------\n"
# define S S_0 S_1

# define W_0 "\n.88b  d88. d888888b d8b   db d888888b"
# define W_1 " d888888b  .d8b.  db      db   dD \n"
# define W_2 "88'YbdP`88   `88'   888o  88   `88'  "
# define W_3 " `~~88~~' d8' `8b 88      88 ,8P' \n"
# define W_4 "88  88  88    88    88V8o 88    88   "
# define W_5 "    88    88ooo88 88      88,8P   \n"
# define W_6 "88  88  88    88    88 V8o88    88   "
# define W_7 "    88    88~~~88 88      88`8b   \n"
# define W_8 "88  88  88   .88.   88  V888   .88.  "
# define W_9 "    88    88   88 88booo. 88 `88. \n"
# define W_10 "YP  YP  YP Y888888P VP   V8P Y888888P"
# define W_11 "    YP    YP   YP Y88888P YP   YD \n\n"

# define HI "Hello.. feel free to send me messages at : [" RED "%u" RST "] :)\n"
# define MSG UDL "\n\tMessage received from " RED "[%u]" RST " :\n\n\"%s\"\n"
# define WLC W_0 W_1 W_2 W_3 W_4 W_5 W_6 W_7 W_8 W_9 W_10 W_11

typedef struct s_minitalk_client
{
	uint8_t	flags;
	size_t	msg_size;
}				t_client;

typedef struct s_minitalk_server
{
	size_t	msg_size;
	char	*msg;
	uint8_t	flags;
	size_t	offset;
	pid_t	clt_pid;
}				t_server;

# define

#endif

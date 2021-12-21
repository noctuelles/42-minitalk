/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_client.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:31:36 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/21 15:32:42 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdint.h>

typedef struct s_minitalk_client
{
	uint8_t	flags;
	size_t	msg_size;
}				t_client;


typedef enum e_client_flags
{
	CRDOK=0x01
}				t_client_flags;

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/21 13:26:15 by plouvel           #+#    #+#              #
#    Updated: 2021/12/24 02:14:40 by plouvel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS_DIR	=	objs/

SRCS_DIR	=	srcs/

SRCS_CLIENT	=	client/client.c		\
				client/utils.c

SRCS_SERVER	=	server/server.c		\
				server/utils.c

OBJS_CLIENT	=	$(addprefix $(OBJS_DIR), $(SRCS_CLIENT:.c=.o))

OBJS_SERVER	=	$(addprefix $(OBJS_DIR), $(SRCS_SERVER:.c=.o))

CFLAGS		=	-Wall -Werror -Wextra -I includes -I libft/includes

CC			=	cc

NAME		=	minitalk

RM			=	rm -rf

$(NAME):		makeft client server

client:			$(OBJS_CLIENT)
				$(CC) $(CFLAGS) $^ -o client -L ./libft -lft

server:			$(OBJS_SERVER)
				$(CC) $(CFLAGS) $^ -o server -L ./libft -lft

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c
				@mkdir -p $(OBJS_DIR) $(OBJS_DIR)client $(OBJS_DIR)server
				${CC} ${CFLAGS} -c $< -o $@

makeft:
				make -C libft all

all:			$(NAME)

clean:
				$(RM) $(OBJS_DIR)
				make -C libft clean

fclean:			clean
				$(RM) client server
				$(RM) libft/libft.a

re:				fclean all

.PHONY:			$(NAME) makeft all clean fclean re

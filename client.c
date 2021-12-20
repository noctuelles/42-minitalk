#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

# define "Unable to send message : the P.I.D might be invalid.\n"
# define "Unabe to send message : the server may has been killed.\n"

typedef enum e_flags
{
	COM=0x01,
	SIGOK=0x02
};

typedef struct s_minitalk
{
	uint8_t	flags;
	size_t	message_size;
	int		current_sig;
	int		can_send;
}				t_minitalk;

static t_minitalk	minitalk;

void	handler(int signum)
{
	if (signum == SIGUSR1)
	{
		if (minitalk.current_sig == SIGUSR1)
			minitalk.can_send = 1; 
	}
	if (signum == SIGUSR2)
	{
		if (minitalk.current_sig == SIGUSR2)
			minitalk.can_send = 1; 
	}
}

int	send_char(pid_t pid, unsigned char c)
{
	size_t	i;

	i = 8;
	while (i)
	{
		minitalk.can_send = 0;
		if (c & (1U << (i - 1)))
		{
			if (kill(pid, SIGUSR1) == -1)
				return (-1);
			minitalk.current_sig = SIGUSR1;
			write(1, "1", 1);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				return (-1);
			minitalk.current_sig = SIGUSR2;
			write(1, "0", 1);
		}
		i--;
		while (!minitalk.can_send)
			;
	}
	write(1, "\n", 1);
}

int	main(int argc, char **argv)
{
	pid_t pid = atoi(argv[1]);
	size_t	i = 0;
	(void) argc;

	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	minitalk.msg_size = strlen(argv[2]);
	while (argv[2][i] != '\0')
	{
		if (send_char(pid, argv[2][i]) == -1)
		{
			puts("Invalid P.I.D");
			return (1);
		}
		i++;
	}
	puts("String sucessfully sended");
	return (0);
}

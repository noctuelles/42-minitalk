#include <unistd.h>
#include <signal.h>
#include <stdio.h>

# define msg1 "1"
# define msg0 "0"

# define ACK_CLIENT_ERROR "Unable to notify client, did you kill it ?!\n"
# define SIGACT_ERROR "Unable to setup signal action.\n"
# define "Multiple client communicating at the same time, aborting.\n"

enum server flags {
	COM=0x01,
	MES_READ=0x02,
	SIZE_READ=0x04
};

typedef struct	s_server
{
	size_t	msg_size;
	char	*msg;
	uint8_t	flags;
	char	c_char;
	size_t	offset;
	pid_t	client_pid;
}					t_server;

int	

void	handle_char(int signum)
{
	if (server.boffset == 7)
		server.c_char = 0;
	if (signum == SIGUSR1)
		server.c_char |= (1U << server.boffset);
	if (server.boffset == 0)
	{
		write(1, &server.c_char, 1);
		server.char_recv++;
		server.boffset = 7;
	}
	else
		server.boffset--;
}

void	read_size(int signum)
{
	if (signum == SIGUSR1)
		server.message_size |= (1U << server.offset);
	if (server.offset == 0)
	{
		server.offset = 7;
	}
}

void	handler(int signum, siginfo_t *siginfo, void *ucontext)
{
	pid_t	sender_pid;

	sender_pid = siginfo->si_pid;
	handle_char(signum); 
	kill(sender_pid, signum);
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
}

int	main(void)
{
	if (!set_sigaction())
		return (-1);
	while (1)
	{
		while (!(server.flags & MALLOC))
			pause();
		server.msg = malloc(server.msg_size * sizeof(char));
		if (!server.msg)
			return (1);
		while (!(server.flags & RDOK))
			pause();
	}
	return (0);
}

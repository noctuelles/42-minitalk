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
	size_t	message_size;
	size_t	char_recv;
	char	c_char;
	size_t	offset;
	pid_t	client_pid;
}					t_server;

t_server	server = {
	.message_size = 0,
	.c_char = 0,
	.offset = sizeof(size_t) * 8,
	.client_pid = 0
};

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

int	main()
{
	struct sigaction	sigact;
	server.boffset = 7;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = SA_SIGINFO;
	sigact.sa_sigaction = &handler;
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	while (1)
		pause();
}

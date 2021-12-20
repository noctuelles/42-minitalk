

#include <stdio.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>


int	main()
{
	fputs(WLC, stdout);
	printf(HI, getpid());
	fputs(S, stdout);
	printf(MSG, 1239, "Bonjour");
}

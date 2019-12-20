/* Signals Demo by Andrei Borovsky <borovsky@tochka.ru> */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void term_handler(int i){
	printf ("Terminating\n");
	exit(EXIT_SUCCESS);
}

int main(int argc, char ** argv){
	struct sigaction sa;
	sigset_t newset;
	int sig;
	sa.sa_handler = term_handler;
	sigaction(SIGTERM, &sa, 0);
	printf("My pid is %i\n", getpid());
	printf("Waiting...\n");
	sigemptyset(&newset);
	sigaddset(&newset, SIGHUP);
	sigprocmask(SIG_BLOCK, &newset, 0);
	while(!sigwait(&newset, &sig))
    	printf("SIGHUP recieved\n");
	return EXIT_FAILURE;
}

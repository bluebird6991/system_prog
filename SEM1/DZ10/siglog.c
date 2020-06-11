/* Signals Demo by Andrei Borovsky <borovsky@tochka.ru> */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void term_handler(int sig){
	printf("Signal %i - %s\n", sig, sys_siglist[sig]);
	exit(EXIT_SUCCESS);
}

int main(int argc, char ** argv){
	sigset_t sset;
	int sig;
	struct sigaction sa;
	sa.sa_handler = term_handler;
	sigaction(SIGTERM, &sa, 0);
	sigfillset(&sset);
	sigdelset(&sset, SIGTERM);
	sigprocmask(SIG_SETMASK, &sset, 0);
	printf("My pid is %i\n", getpid());
	while(!sigwait(&sset, &sig)){
		printf("Signal %i - %s\n", sig, sys_siglist[sig]);
	}
    //printf("%s\n", strsignal(sig));
  	return EXIT_SUCCESS;
}

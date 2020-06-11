#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int sigInput(int* inputPtr){
	printf("Input signal number(1-31):\n\r>>");
	scanf("%d", inputPtr);
	if(*inputPtr>=1 && *inputPtr<=31)
		return 0;
	else
		return 1;
}
void sigHandler(int sigNum){ printf("-----------------\n\rHandler starts...\n\r");
	if (sigNum == SIGHUP){ 
            printf("Received SIGHUP(1)\n\r");
        }else if(sigNum == SIGINT){
            printf("Received SIGINT(2)\n\r");
        }else if(sigNum == SIGQUIT){
            printf("Received SIGQUIT(3)\n\r");
        }else if(sigNum == SIGILL){
            printf("Received SIGILL(4)\n\r");
        }else if(sigNum == SIGTRAP){
            printf("Received SIGTRAP(5)\n\r");
        }else if(sigNum == SIGABRT){
            printf("Received SIGABRT(6)\n\r");
        }else if(sigNum == SIGBUS){
            printf("Received SIGBUS(7)\n\r");
        }else if(sigNum == SIGFPE){
            printf("Received SIGFPE(8)\n\r");
        }else if(sigNum == SIGKILL){
            printf("Received SIGKILL(9)\n\r");
        }else if(sigNum == SIGUSR1){
            printf("Received SIGUSR1(10)\n\r");
        }else if(sigNum == SIGSEGV){
            printf("Received SIGSEGV(11)\n\r");
        }else if(sigNum == SIGUSR2){
            printf("Received SIGUSR2(12)\n\r");
        }else if(sigNum == SIGPIPE){
            printf("Received SIGPIPE(13)\n\r");
        }else if(sigNum == SIGALRM){
            printf("Received SIGALRM(14)\n\r");
        }else if(sigNum == SIGTERM){
            printf("Received SIGTERM(15)\n\r");
        }else if(sigNum == SIGSTKFLT){
            printf("Received SIGSTKFLT(16)\n\r");
        }else if(sigNum == SIGCHLD){
            printf("Received SIGCHLD(17)\n\r");
        }else if(sigNum == SIGCONT){
            printf("Received SIGCONT(18)\n\r");
        }else if(sigNum == SIGSTOP){
            printf("Received SIGSTOP(19)\n\r");
        }else if(sigNum == SIGTSTP){
            printf("Received SIGTSTP(20)\n\r");
        }else if(sigNum == SIGTTIN){
            printf("Received SIGTTIN(21)\n\r");
        }else if(sigNum == SIGTTOU){
            printf("Received SIGTTOU(22)\n\r");
        }else if(sigNum == SIGURG){
            printf("Received SIGURG(23)\n\r");
        }else if(sigNum == SIGXCPU){
            printf("Received SIGXCPU(24)\n\r");
        }else if(sigNum == SIGXFSZ){
            printf("Received SIGXFSZ(25)\n\r");
        }else if(sigNum == SIGVTALRM){
            printf("Received SIGVTALRM(26)\n\r");
        }else if(sigNum == SIGPROF){
            printf("Received SIGPROF(27)\n\r");
        }else if(sigNum == SIGWINCH){
            printf("Received SIGWINCH(28)\n\r");
        }else if(sigNum == SIGIO){
            printf("Received SIGIO(29)\n\r");
        }else if(sigNum == SIGPWR){
            printf("Received SIGPWR(30)\n\r");
        }else if(sigNum == SIGSYS){
            printf("Received SIGSYS(31)\n\r");
        }else{
            printf("Received bad signal number(not 1-31)!!!\n\r");
        }
    printf("Handler ends...\n\r---------------\n\r");
}
int sigCatcher(void){ printf("-----------------------------------------------------\n\rCatcher starts 
    (settings for signals interception)...\n\r");
        if (signal(SIGHUP, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGHUP(1)!!!\n\r");
        }
        if (signal(SIGINT, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGINT(2)!!!\n\r");
        }
        if (signal(SIGQUIT, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGQUIT(3)!!!\n\r");
        }
        if (signal(SIGILL, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGILL(4)!!!\n\r");
        }
        if (signal(SIGTRAP, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGTRAP(5)!!!\n\r");
        }
        if (signal(SIGABRT, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGABRT(6)!!!\n\r");
        }
        if (signal(SIGBUS, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGBUS(7)!!!\n\r");
        }
        if (signal(SIGFPE, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGFPE(8)!!!\n\r");
        }
        if (signal(SIGKILL, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGKILL(9) (by design in 
                linux)!!!\n\r");
        }
        if (signal(SIGUSR1, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGUSR1(10)!!!\n\r");
        }
        if (signal(SIGSEGV, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGSEGV(11)!!!\n\r");
        }
        if (signal(SIGUSR2, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGUSR2(12)!!!\n\r");
        }
        if (signal(SIGPIPE, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGPIPE(13)!!!\n\r");
        }
        if (signal(SIGALRM, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGALRM(14)!!!\n\r");
        }
        if (signal(SIGTERM, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGTERM(15)!!!\n\r");
        }
        if (signal(SIGSTKFLT, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGSTKFLT(16)!!!\n\r");
        }
        if (signal(SIGCHLD, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGCHLD(17)!!!\n\r");
        }
        if (signal(SIGCONT, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGCONT(18)!!!\n\r");
        }
        if (signal(SIGSTOP, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGSTOP(19) (by design in 
                linux)!!!\n\r");
        }
        if (signal(SIGTSTP, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGTSTP(20)!!!\n\r");
        }
        if (signal(SIGTTIN, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGTTIN(21)!!!\n\r");
        }
        if (signal(SIGTTOU, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGTTOU(22)!!!\n\r");
        }
        if (signal(SIGURG, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGURG(23)!!!\n\r");
        }
        if (signal(SIGXCPU, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGXCPU(24)!!!\n\r");
        }
        if (signal(SIGXFSZ, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGXFSZ(25)!!!\n\r");
        }
        if (signal(SIGVTALRM, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGVTALRM(26)!!!\n\r");
        }
        if (signal(SIGPROF, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGPROF(27)!!!\n\r");
        }
        if (signal(SIGWINCH, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGWINCH(28)!!!\n\r");
        }
        if (signal(SIGIO, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGIO(29)!!!\n\r");
        }
        if (signal(SIGPWR, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGPWR(30)!!!\n\r");
        }
        if (signal(SIGSYS, sigHandler) == SIG_ERR){ printf("Can't catch the signal SIGSYS(31)!!!\n\r");
        }
    printf("Catcher ends...\n\r---------------\n\r"); return 0;
}
int main(void){ pid_t sigPid; int* sigPtr=malloc(sizeof(int)); while(sigInput(sigPtr)); printf("Parent 
    acquired signal number...\n\r"); printf("Parent starts fork...\n\r"); if ((sigPid=fork())==0){
        printf("Child was forked...\n\r"); if ((int)sigPid == 0){ sigCatcher();
        }
        while(1);
        }else{
        printf("Parent wait 1s for fun...\n\r"); sleep(1); printf("Parent sends signal number %d to 
        child...\n\r", *sigPtr);
            kill(sigPid, *sigPtr); printf("Parent wait 1s for fun...\n\r"); sleep(1); if (*sigPtr != 9){ 
                printf("Parent additionally brutally kills child for good complete of program...\n\r");
        kill(sigPid, 9);
            }else printf("Parent additionally brutally kills no required\n\r");
        }
        return 0;
}

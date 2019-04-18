#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

void sighandler(int);

int trigger = 0;

int main(int argc, char **argv){
	
	int pFile, oflags;
	int rd;
	struct sigaction action, oa;
	char buffer[10] = "";

	// Opens to device file
	pFile = open("/dev/tetrix", O_RDWR);
	if (pFile < 0) {
		fprintf (stderr, "tetrix module isn't loaded\n");
		return 1;
	}

	// Setup signal handler
	memset(&action, 0, sizeof(action));
	action.sa_handler = sighandler;
	action.sa_flags = SA_SIGINFO;
	sigemptyset(&action.sa_mask);
	sigaction(SIGIO, &action, NULL);
	fcntl(pFile, F_SETOWN, getpid());
	oflags = fcntl(pFile, F_GETFL);
	fcntl(pFile, F_SETFL, oflags | FASYNC);

	while(1){
		if(trigger){
			rd = read(pFile, buffer, 10);
			buffer[rd] = '\0';
			printf("%s\n", buffer);
			trigger = 0;
			close(pFile);
			pFile = open("/dev/tetrix", O_RDWR);
			fcntl(pFile, F_SETOWN, getpid());
			oflags = fcntl(pFile, F_GETFL);
			fcntl(pFile, F_SETFL, oflags | FASYNC);
		}
	}

	close(pFile);

	return 0;
}

void sighandler(int signo)
{
	trigger = 1;
}

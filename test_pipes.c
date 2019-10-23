#include <errno.h>
#include <stdio.h>
#include <unistd.h>
//#include <sys/wait.h>

int main(int argc, char* argv[]) {
	pid_t pid1, pid2, pid3;
	int pipefd[2];
	// The two commands we'll execute.  In this simple example, we will pipe
	// the output of `ls` into `wc`, and count the number of lines present.
	char *argv1[] = {"ls", NULL};
	char *argv2[] = {"cat", NULL};
	char *argv3[] = {"cat", NULL};
	// Create a pipe.
	pipe(pipefd);
	// Create our first process.
	pid1 = fork();
	if (pid1 == 0) { //1st
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		execvp(argv1[0], argv1);
		perror("exec");
		return 1;
	}
	pid2 = fork();
	if (pid2 == 0) { // 2nd
		//dup2(pipefd[0], STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
	    close(STDERR_FILENO);
		close(pipefd[0]);
		execvp(argv2[0], argv2);
		perror("exec");
		return 1;
	}
	pid3 = fork();
	if (pid3 == 0) { // 2nd
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		execvp(argv3[0], argv3);
		perror("exec");
		return 1;
	}
   /*pipe(pipefd);
   //dup2(pipefd[1], STDOUT_FILENO);
   close(pipefd[0]);
   // Create our second process.
   pid3 = fork();
   if (pid3 == 0) { // 3nd
      // Hook stdin up to the read end of the pipe and close the write end of
      // the pipe which is no longer needed by this process.
      dup2(pipefd[0], STDIN_FILENO);
      close(pipefd[1]);
      // Similarly, exec `wc -l`.
      execvp(argv3[0], argv3);
      perror("exec");
      return 1;
  }*/
   // Close both ends of the pipe.  The respective read/write ends of the pipe
   // persist in the two processes created above (and happen to be tying stdout
   // of the first processes to stdin of the second).
   close(pipefd[0]);
   close(pipefd[1]);
   //close(STDERR_FILENO);
   // Wait for everything to finish and exit.
   waitpid(pid1);
   waitpid(pid2);
   waitpid(pid3);
   return 0;
}

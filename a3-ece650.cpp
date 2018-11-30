#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string>
#include <signal.h>
#include <vector>


void ouch(int sig)
{
	exit(0);
}

int main(int argc,char **argv)
{
	pid_t pid;
	std::vector<pid_t> pid_num;
	int i = 0;
	int pipe1_2[2];
	int pipe2_3[2];

	pipe(pipe1_2);
	pipe(pipe2_3);
	
	for(i = 0;i < 3;i++)
	{
		pid = fork();
		pid_num.push_back(pid);
		if(pid == 0)
			break;
	}


	if(i == 0)
	{		
		
		std::cout << getpid();
		
		dup2(pipe1_2[1],STDOUT_FILENO);
		close(pipe1_2[0]);
		close(pipe1_2[1]);
		close(pipe2_3[0]);
		close(pipe2_3[1]);
    	execv("./rgen",argv);
    	std::cerr << "Error: an error occurred in execv" << std::endl;
	 }
	

	if(i == 1)
	{
		char *argv[]={"python","./a1-ece650.py",NULL};
		dup2(pipe1_2[0],STDIN_FILENO);
		dup2(pipe2_3[1],STDOUT_FILENO);
		close(pipe2_3[0]);
		close(pipe2_3[1]);
		close(pipe1_2[0]);
		close(pipe1_2[1]);
		execv("/usr/bin/env",argv);
		std::cerr << "Error: an error occurred in execv" << std::endl;
	}

	if(i == 2)
	{
		dup2(pipe2_3[0],STDIN_FILENO);
		close(pipe1_2[0]);
		close(pipe1_2[1]);
		close(pipe2_3[0]);
		close(pipe2_3[1]);
		execv("./a2-ece650",argv);
		std::cerr << "Error: an error occurred in execv1" << std::endl;
	}	


	else
	{
		std::string message;
		dup2(pipe2_3[1],STDOUT_FILENO);
		close(pipe2_3[0]);
		close(pipe2_3[1]);
		close(pipe1_2[0]);
		close(pipe1_2[1]);
		(void) signal(SIGTERM, ouch);
		while(1)
		{

			getline(std::cin,message);

			if(message == "")
			{
				//kill(0,SIGTERM);
				exit(0);
			}

			else if(message[0] == 's')
			{
				std::cout << message << std::endl;
			}
		}

		while(wait(NULL) != -1);

	}


	return 0;
}

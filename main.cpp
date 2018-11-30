#include "rgen.h"


pid_t init_pid,pid_num;

int main(int argc,char **argv)
{
	struct argument arg = {10,5,5,20};
	int opt;

	init_pid = getppid();
	while((opt = getopt(argc,argv,"s:n:l:c:")) != -1)
	{
		switch(opt)
		{
			case 's': 
				if(atoi(optarg) < 2 || atoi(optarg) > 10)
					std::cerr << "Error: error message." << std::endl;
				else
					arg.s_k = atoi(optarg); 
				break;

			case 'n': 
				if(atoi(optarg) < 1)
					std::cerr << "Error: error message." << std::endl;
				else
					arg.n_k = atoi(optarg); 
				break;

			case 'l': 
				if(atoi(optarg) < 5)
					std::cerr << "Error: error message." << std::endl;
				else
					arg.l_k = atoi(optarg); 
					break;
			case 'c': 
				if(atoi(optarg) < 1)
					std::cerr << "Error: error message." << std::endl;
				else
					arg.c_k = atoi(optarg); 
				break;

			case '?': std::cerr << "Error:option -" << (char)optopt
								<< " requires an argument." << std::endl;  
		}
	}

	if(optind < argc)
		std::cerr << "Found positional argument" << std::endl;
	for(;optind < argc;optind++)
		std::cerr << "Non-optional argument:" << argv[optind] << std::endl;

	while(1)
	{
		pid_num = getppid();
		if(pid_num != init_pid)
		{
			std::cout << "quit" << std::endl;
			exit(0);
		}
		generate_street(arg);
	}

	return 0;
}
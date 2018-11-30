#include "rgen.h"
#include <unistd.h> 

extern pid_t init_pid;

typedef struct
{
	int x;
	int y;
}point;

typedef struct 
{	
	point src;
	point dst;
}line;

int street_number = 0;




int check_overlap(int street[],int length)
{
	for(int i = 0;i < length;i++)
		for(int j = i + 1;j < length;j++)
	{
		if(street[2*i] == street[2*j] && street[2*i+1] == street[2*j+1] && street[2*i+2] == street[2*j+2] && street[2*i+3] == street[2*j+3]\
			|| street[2*i] == street[2*j+2] && street[2*i+1] == street[2*j+3] && street[2*i+2] == street[2*j+2] && street[2*i] == street[2*j+1])
			return 1;
	}
	return 0;
}



int get_random(struct rand_argument rand_arg)
{
	unsigned int num,first;

	std::ifstream urandom("/dev/urandom");
	if(urandom.fail())
	{
		std::cerr << "Error: cannot open /dev/urandom\n";
		return 1;
	}

	urandom.read((char *)&num,sizeof(int));
	if(num % 2 == 1)
	{
		urandom.read((char *)&num,sizeof(int));
		first = num % (rand_arg.value_range + 1);
	}
		
	else
	{
		urandom.read((char *)&num,sizeof(int));
		first = -(num % (rand_arg.value_range + 1));
	}
	
	urandom.close();
	return first;
}


int check_repeat(int length,int street[],int first,int second)
{
	if(length == 0)
		return 0;
	else
	{
		for(int i = 0;i < length;i+=2)
		{
			if(street[i] == first && street[i + 1] == second)
				return -1;
		}
	}
	return 0;
}

int intersect(line first,line second,int first_index,int second_index)
{
	float x1,x2,x3,x4,y1,y2,y3,y4;
	float xnum,xden,xcoor,ynum,yden,ycoor;

	x1 = first.src.x;
	y1 = first.src.y;
    x2 = first.dst.x;
    y2 = first.dst.y;

    x3 = second.src.x;
    y3 = second.src.y;
    x4 = second.dst.x,
    y4 = second.dst.y;

    xnum = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4));
    xden = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4));
	
	if(xden == 0)
	{
		if(x1 == x2 && x1 == x4)
		{
			if((std::min(y3,y4) <= y1 && y1 <= std::max(y3,y4) && std::min(y3,y4) <= y2 && y2 <= std::max(y3,y4)) || \
			 (std::min(y1,y2) <= y3 && y3 <= std::max(y1,y2) && std::min(y1,y2) <= y4 && y4 <= std::max(y1,y2)))
				return -1;				
		}

		else
		{
			float k = (y1 - y2)/(x1 - x2);
            float b = y1 - x1 * ((y1 - y2)/(x1 - x2));
            if(k * x3 + b - y3 < 0.00001)
            {
            	if((std::min(x3,x4) <= x1 && x1 <= std::max(x3,x4) && std::min(x3,x4) <= x2 && x2 <= std::max(x3,x4)) || \
			 	(std::min(x1,x2) <= x3 && x3 <= std::max(x1,x2) && std::min(x1,x2) <= x4 && x4 <= std::max(x1,x2)))
					return -1;
            }
		}
	}

	else
	{
		if(second_index != first_index + 1)
		{
			xcoor =  xnum / xden;
	    	ynum = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4);
	    	yden = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
	    	ycoor = ynum / yden;

	    	if((std::min(x1,x2) <= xcoor && xcoor <= std::max(x1,x2)) && (std::min(x3,x4) <= xcoor && xcoor <= std::max(x3,x4)))
		      	return -1;
	     	
	     }
	} 
	return 0;    
}


int check_cross(int count,line street_info[])
{
	if(count == 0 || count == 2)
		return 0;

	for(int j = 0;j < count/2 - 1;j++)
	{
		if(intersect(street_info[j],street_info[count/2 - 1],j,(count/2 - 1)) == -1)
			return -1;
	}
	return 0;

}


int calculate_street(struct rand_argument rand_arg,int street[])
{
	int try_time = 0;
	int first,second;

	line *street_info = new line[rand_arg.segment_num];

	
	for(int i = 0;i < 2 * rand_arg.segment_num + 2;i+=2)
	{
		first = get_random(rand_arg);
		second = get_random(rand_arg);

		if(i >= 2)
		{
			street_info[i/2 - 1].src = {street[i - 2],street[i - 1]};
			street_info[i/2 - 1].dst = {first,second};
		}
		//while(check_repeat(i,street,first,second) == 1)
		while((first == street_info[i/2 - 1].src.x) && (second == street_info[i/2 - 1].src.y) || (check_cross(i,street_info) == -1)\
			|| (check_repeat(i,street,first,second)) == -1)
		{
			if(try_time > 75)
			{
				std::cerr << "Error: failed to generate valid input for 25 simultaneous attempts" << std::endl;
				delete []street_info;
				return -1;
			}
			first = get_random(rand_arg);
			second = get_random(rand_arg);
			street_info[i/2 - 1].dst = {first,second};
			try_time++;
		}
		street[i] = first;
		street[i + 1] = second;
	}
	delete []street_info;	
	return 1;
}


int add_street(int count,struct rand_argument rand_arg)
{
	int *street;
	char name = 'A';

	int count1 = count/26;
	int count2 = count%26;
	
	street = new int[2 * rand_arg.segment_num + 2];

	int ret = calculate_street(rand_arg,street);

	if(ret == 1)
	{	
		std::cout << "a \""; 

		for(int i = 0;i < count1 + 1;i++)
			std::cout << (char)(name + count2); 
		std::cout << " street\" ";

		for(int i = 0;i < 2 * rand_arg.segment_num + 2;i+=2)
		{
			 std::cout << "(" << street[i] << "," << street[i + 1] << ") ";
		}

		std::cout << std::endl;
		delete []street;
	}

	else
	{
		delete []street;
		kill(init_pid,SIGTERM);
		std::cout << "quit" << std::endl;
		exit(0);
	}
}


void remove_street()
{
	char name = 'A';

	for(int i = 0;i < street_number;i++)
	{
		int count1 = i/26;
		int count2 = i%26;
		std::cout << "r \"";
		for(int j = 0;j < count1+1;j++)
			std::cout << (char)(name + count2); 
		std::cout << " street\"" << std::endl; 
	}
}


int output_graph(struct rand_argument rand_arg)
{
	remove_street();		
	
	for(int i = 0;i < rand_arg.street_num;i++)
	{
		if(add_street(i,rand_arg) == -1)
			return -1;
	}

	std::cout << "g" << std::endl;
	street_number = rand_arg.street_num;
	sleep(rand_arg.wait_second);
	
}


int generate_street(struct argument arg)
{
	std::ifstream urandom("/dev/urandom");
	struct rand_argument rand_arg;
	if(urandom.fail())
	{
		std::cerr << "Error: cannot open /dev/urandom\n";
		return 1;
	}

	unsigned int num;
	urandom.read((char *)&num,sizeof(int));
	while(num % (arg.s_k + 1) < 2)
		urandom.read((char *)&num,sizeof(int));
	rand_arg.street_num = num % (arg.s_k + 1);
	//std::cout << "number of street:" << rand_arg.street_num << std::endl;
	
	urandom.read((char *)&num,sizeof(int));
	while(num % (arg.n_k + 1) == 0)
		urandom.read((char *)&num,sizeof(int));
	rand_arg.segment_num = num % (arg.n_k + 1);
	//std::cout << "number of segment:" << rand_arg.segment_num << std::endl;
	
	if(arg.l_k == 5)
		rand_arg.wait_second = 5;
	else
	{
		urandom.read((char *)&num,sizeof(int));
		while(num % (arg.l_k + 1) < 5)
			urandom.read((char *)&num,sizeof(int));
		rand_arg.wait_second = num % (arg.l_k + 1);
	}
	//std::cout << "wait_second:" << rand_arg.wait_second << std::endl;
	

	urandom.read((char *)&num,sizeof(int));
	while(num % (arg.c_k + 1) == 0)
		urandom.read((char *)&num,sizeof(int));
	rand_arg.value_range = num % (arg.c_k + 1);
	//std::cout << "value:" << rand_arg.value_range << std::endl;
	
	urandom.close();
	//sleep(rand_arg.wait_second);
	output_graph(rand_arg);
}
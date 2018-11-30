#ifndef _RGEN_H
#define _RGEN_H

#include <signal.h>
#include <iostream>
#include <unistd.h>
#include <fstream>


struct argument
{
	int s_k;
	int n_k;
	int l_k;
	int c_k;
};

struct rand_argument
{
	int street_num;
	int segment_num;
	int wait_second;
	int value_range;
};

int generate_street(struct argument arg);
int output_graph(struct rand_argument rand_arg);
void remove_street(void);
int add_street(int count,struct rand_argment rand_arg);


#endif
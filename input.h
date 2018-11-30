#ifndef INCLUDE_H
#define INCLUDE_H

#include <regex>
#include <iostream>
#include <string.h>
#include <stdlib.h>


#define ERROR      -1
#define V_E_INFO    1
#define PATH        2
#define MAX         100
#define TERMINATE   -2





void clear_data(int &vertices_num,int &edge_num,int edge[]);
int check_input(int vertices_num,int edge_num,int edge[],char symbol);
int get_input(int &vertices_num,int &edge_num,int edge[],int src_dst[]);
void print_graph(int vertices_num,int edge_num,int edge[]);


#endif

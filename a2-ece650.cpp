#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "Graph1.h"
#include "input.h"



int main(int argc,char **argv)
{
    int vertices_num = 0,edge_num = 0;
    int edge[MAX];
    int ret = 1;
    int src_dst[2];

    memset(edge,0,MAX);
    
    while(ret != TERMINATE)
    {
        ret = get_input(vertices_num,edge_num,edge,src_dst);
        if(ret == V_E_INFO)
            print_graph(vertices_num,edge_num,edge);
        
        if(ret == PATH)
        {
            Graph Adjacency_table(vertices_num,edge_num,edge);
            ret = Adjacency_table.find_shortest_path(src_dst[0],src_dst[1]);
        }  
    }
    return 0;
}

#ifndef _GRAPH_H
#define _GRAPH_H

#include <stack>
#include <iostream>
#include <queue>
#include "input.h"


using namespace std;



class ArcNode
{
    private:
        int value;
        ArcNode *next;
    
    public:
        ArcNode(int , ArcNode * = nullptr);
        void set_next(ArcNode *);
        ArcNode *get_next() const;
        int get_value() const;
        void set_value(int);
};



class List
{   
    private:
        int value;
        ArcNode *firstnode;
    public:
        List(int = 0,ArcNode * = nullptr);
        ~List();
        ArcNode *Pop();
        void Push(int);
        void clear_list();
        int get_value() const;
        int is_exist(int) const;
        ArcNode *get_firstnode() const;
        void set_value(int);
        void dfs_find_path() const;
        void set_firstnode(ArcNode *);
        void print() const;
};



class Graph
{       
    private:
        List *list;
        int vertices_num;
        int edge_num;
   
    public:
        Graph(int,int,int []);
        ~Graph();
        int get_vertices_num() const;
        int get_edge_num() const;
        List *get_list(int);
        void print() const;
        void dfs_print_path(int,int) const;
        void dfs_find_path(int,int,int [],stack<int> &) const;
        void dfs_print(int) const;
        void dfs_non_recursive() const;
        int find_shortest_path(int,int) const;
        void dfs(int,int []) const;
};

#endif
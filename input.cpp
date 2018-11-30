#include "input.h"

using namespace std;



void print_graph(int vertices_num,int edge_num,int edge[])
{
    cout << "V " << vertices_num << endl;
    cout << "E " << "{";
    for(int i = 0;i < edge_num;i+=2)
    {
        cout << "<" << edge[i] << "," << edge[i+1] << ">";
        if(i != edge_num - 2)
            cout << ",";
    }
    cout << "}" << endl << endl;
}


void clear_data(int &vertices_num,int &edge_num,int edge[])
{
    memset(edge,0,MAX);
    vertices_num = 0;
    edge_num = 0;
}


int check_input(int vertices_num,int edge_num,int info[],char symbol)
{
    if(symbol == 'V')
    {
        for(int i = 0;i < edge_num; i += 2)
       {      
            if(info[i] >= vertices_num || info[i+1] >= vertices_num)
            {   
                cerr << "Error: vertex " << (info[i] >= vertices_num? info[i] : info[i+1]) << " does not exist" << endl << endl;
                return ERROR;
            }

            if(info[i] == info[i+1])
            {
                cerr << "Error: vertices on an edge should be different" << endl << endl;
                return ERROR;
            }
        }
        return V_E_INFO;
    }

    else
    {
        if(info[0] ==  info[1])
        {
            cerr << "Error: the starting vertex is same as the ending vertex" << endl << endl;
            return ERROR;
        }

        if(info[0] >= vertices_num || info[1] >= vertices_num)
        {
            cerr << "Error: ask for a path that vertex doesn't exist" << endl << endl;
            return ERROR;
        }
        return PATH;
    }
}


int get_input(int &vertices_num,int &edge_num,int edge[],int src_dst[])
{
    char a[100];

    string vertices_info;
    string edge_info;

    getline(cin,vertices_info);
    if(vertices_info == "quit")
    { 
        exit(0);
    }

    if(vertices_info[0] == 'V')
    {
        clear_data(vertices_num,edge_num,edge);
        getline(cin,edge_info);
        vertices_num = atoi(&vertices_info[2]);
        regex reg1("\\d+");
        sregex_iterator it(edge_info.begin(), edge_info.end(), reg1);
        sregex_iterator end;
        for(; it != end; ++it)
        {
            edge[edge_num] = stoi(it-> str());
            edge_num++;
        }

        return check_input(vertices_num,edge_num,edge,'V');
    }

    else if(vertices_info[0] == 's')
    {  
        int j = 0;
        regex reg1("\\d+");
        sregex_iterator it(vertices_info.begin(), vertices_info.end(), reg1);
        sregex_iterator end;
        
        for(; it != end; ++it)
        {
            src_dst[j] = stoi(it-> str());
            j++;
        }
        return check_input(vertices_num,edge_num,src_dst,'s');
    }
        
}

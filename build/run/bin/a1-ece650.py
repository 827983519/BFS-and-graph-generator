#!/usr/bin/env python

import re
import sys
from ag_intersection import *

my_dict = {}

def instruction():
     print "\nPlease enter commnd:\n"
     print "a--add a street, \nc--change a street, \nr--remove a street, \ng--generate a graph\n"


def get_command():
    line = sys.stdin.readline()
    if 'quit' in line:
        sys.stdout.write("quit")
        sys.stdout.flush()
        sys.exit(0)
    else:    
        line.strip()
        a = line[:-1]
        return a

def check_command(line): 
    print "check_command"
    sp = re.split(r'\s',line)   
    command1 = sp[0].strip()
    
    if command1 != 'a' and command1 != 'c' and command1 != 'r' and command1 != 'g':
        sys.stderr.write("Error: unknown command \""+command1+"\"\n")
        return -1    
    elif command1 == 'a':
        return check_command_format("a",line)
    
    elif command1 == 'c':
        return check_command_format("c",line)

    elif command1 == 'r':
        return check_command_format("r",line) 

    elif command1 == 'g':
        return check_command_format("g",line)   
    
def check_command_format(input,line):
    if input == "a" :
        pa = re.compile(r'a +"(.+)" +((\( *-?\d+.?-?\d* *, *-?\d+.?-?\d* *\) *)+)')  
        if pa.search(line) == None:
            sys.stderr.write("Error: wrong command format\n")
            return -1
        else:
            sp = re.split(r'\s"|"\s',line)
            str_name = pa.search(line).group(1)
            str_num = pa.search(line).group(2)
    
            num_patt = re.compile(r'\d+')

            pa1 = re.compile(r'\(-?\d+,-?\d+\) *')
            check_reap =  pa1.findall(line)
            
            
            if num_patt.findall(str_num) !=  num_patt.findall(sp[2]):
                sys.stderr.write("Error: wrong command format\n")
                return -1

            for i in str_name:
                if i.isalpha() == False and i != ' ':
                    sys.stderr.write("Error: the name of street should consist of alphabetical and space characters")
                    return -1

            for i in str_num:
                if i == '.':
                    sys.stderr.write("Error: the coordinate should be integer\n")
                    return -1

            for i in check_reap:
                if check_reap.count(i) != 1:
                    sys.stderr.write("Error: coordinate points are repeated\n")
                    return -1
            
            if my_dict.has_key(str_name.lower()):
                sys.stderr.write("Error: street already exists.\n")

            my_dict[str_name.lower()] = str_num
            return 1
    
    if input == "c" :
        pa = re.compile(r'c +"(.+)" +((\( *-?\d+.?-?\d* *, *-?\d+.?-?\d* *\) *)+)')
        if pa.search(line) == None:
            sys.stderr.write("Error: wrong command format\n")
            return -1

        else:
            sp = re.split(r'\s"|"\s',line)
            str_name = pa.search(line).group(1)
            str_num = pa.search(line).group(2)

            num_patt = re.compile(r'\d')

            pa1 = re.compile(r'\(-?\d+,-?\d+\) *')
            check_reap =  pa1.findall(line)

            for i in str_num:
                if i == '.':
                    sys.stderr.write("Error: the coordinate should be integer\n")
                    return -1
            if my_dict.has_key(str_name.lower()) == False:
                sys.stderr.write("Error: \'c\' or \'r\' specified for a street that does not exist\n")
                return -1

            if num_patt.findall(str_num) !=  num_patt.findall(sp[2]):
                sys.stderr.write("Error: wrong command format\n")
                return -1
            
            else:
                my_dict[str_name.lower()] = str_num
                return 1

    if input == "r" :
        sp = re.split(r'\s"|"\s',line)
        if len(sp) != 2:
            sys.stderr.write("Error: wrong command format\n")
            return -1 
        pa = re.compile(r'r +"(.*)" *')
        if pa.search(line) == None:
            sys.stderr.write("Error: wrong command format\n")
            return -1
        str_name = pa.search(line).group(1)
        if  my_dict.has_key(str_name.lower()) == False:
            sys.stderr.write("Error: \'c\' or \'r\' specified for a street that does not exist\n")
            return -1
        else:
            del my_dict[str_name.lower()]
            return 1

    if input == "g" :
        if len(line) != 1 and line != "g":
            sys.stderr.write("Error: wrong command format\n")
            return -1
        else:
            return "g"


def get_line_segment(street_line):
    
    pattern = re.compile(r'-?\d+')

    for i in range(len(my_dict)): 
        temp = []
        num_list = pattern.findall(my_dict.values()[i])
        for j in range(0,len(num_list) - 2 ,2):        
            temp.append(line(point(int(num_list[j]),int(num_list[j + 1])), point(int(num_list[j + 2]), int(num_list[j + 3]))))

        street_line.append(temp)

def draw_graph():
    message = []
    street_line = []
    get_line_segment(street_line)

    message = get_graph(street_line)
    draw(message)
              
        
def main():
    while True:
        comm = get_command()
        if comm == 0:
            sys.stderr.write("Finish\n")
            break
        else:
            ret = check_command(comm)

        if  ret == 'g':
            draw_graph()

    sys.exit(0)


if __name__ == '__main__':
    main()

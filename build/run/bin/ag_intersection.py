#!/usr/bin/env python
import sys
def pp(x):
    """Returns a pretty-print string representation of a number.
       A float number is represented by an integer, if it is whole,
       and up to two decimal places if it isn't
    """
    if isinstance(x, float):
        if x.is_integer():
            return str(int(x))
        else:
            return "{0:.2f}".format(x)
    return str(x)

class point(object):
    """A point in a two dimensional space"""
    def __init__(self, x, y):
        self.x = float(x)
        self.y = float(y)

    def __repr__(self):
        #return '(' + pp(self.x) + ', ' + pp(self.y) + ')'
        return '(' + "{0:.2f}".format(self.x) + ',' + "{0:.2f}".format(self.y) + ')'


class line(object):
    """A line between two points"""
    def __init__(self, src, dst):
        self.src = src
        self.dst = dst

    def __repr__(self):
        return  str(self.src) + '-->' + str(self.dst)


def intersect (l1, l2):
    """Returns a point at which two lines intersect"""
    x1, y1 = l1.src.x, l1.src.y
    x2, y2 = l1.dst.x, l1.dst.y

    x3, y3 = l2.src.x, l2.src.y
    x4, y4 = l2.dst.x, l2.dst.y

    xnum = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4))
    xden = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4))
    
    leng_l1 = (y1 - y2)*(y1 - y2) + (x1 - x2)*(x1 - x2) 
    leng_l2 = (y3 - y4)*(y3 - y4) + (x3 - x4)*(x3 - x4) 
 
    if (x1 == x3 and y1 == y3 and x2 == x4 and y2 == y4) or (x1 == x4 and y1 == y4 and x2 == x3 and y2 == y3):
        return 7
    if xden == 0:
        if x1 == x2:
            if x3 == x4 == x1:   #on the same line
                if leng_l1 > leng_l2:
                    if max(y1,y2) >= y3 >= min(y1,y2) and max(y1,y2) >= y4 >= min(y1,y2):
                        return 1
                else:
                    if max(y3,y4) >= y1 >= min(y3,y4) and max(y3,y4) >= y2 >= min(y3,y4):
                        return 2

                if max(y1,y2) >= y3 >= min(y1,y2) and not(max(y1,y2) >= y4 >= min(y1,y2)):
                    if y3 > y4:
                        return 3
                    else:
                        return 4

                elif max(y1,y2) >= y4 >= min(y1,y2) and not(max(y1,y2) >= y3 >= min(y1,y2)):
                    if y3 > y4:
                        return 5
                    else:
                        return 6
                else:
                    return -1 
            else:
                return -1

        else:
            k = (y1 - y2)/(x1 - x2)
            b = y1 - x1 * ((y1 - y2)/(x1 - x2))
            if k* x3 + b == y3 :  #on the same line
                if leng_l1 > leng_l2:
                    if max(x1,x2) >= x3 >= min(x1,x2) and max(x1,x2) >= x4 >= min(x1,x2):
                        return 1
                else:
                    if max(x3,x4) >= x1 >= min(x3,x4) and max(x3,x4) >= x2 >= min(x3,x4):
                        return 2

                if max(x1,x2) >= x3 >= min(x1,x2) and not(max(x1,x2) >= x4 >= min(x1,x2)):
                    if x3 > x4:
                        return 3
                    else:
                        return 4
                elif max(x1,x2) >= x4 >= min(x1,x2) and not(max(x1,x2) >= x3 >= min(x1,x2)):
                    if x3 > x4:
                        return 5
                    else:
                        return 6
                else:
                    return -1 
            else:
                return -1
  
    xcoor =  xnum / xden
    ynum = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4)
    yden = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4)
    ycoor = ynum / yden    
    if xcoor < min(x1,x2) or xcoor > max(x1,x2) or xcoor < min(x3,x4) or xcoor > max (x3,x4) or\
    ycoor < min(y1,y2) or ycoor > max(y1,y2) or ycoor < min(y3,y4) or ycoor > max (y3,y4):
        return -1
    
    return point(xcoor, ycoor)

index = {}
id = 0
def get_index(vertics):
    global index,id
    if id == 1000000:
        id = 0

    if len(index) == 0:
        for i in vertics:
            index[id] = i
            id = id + 1
    else:
        for i in index.keys():
            for j in vertics:
                if index[i].x == j.x and index[i].y == j.y:
                    break
                elif [j] == vertics[-1:]:
                    del index[i]
        
        if len(index) == 0:
            id = 0
            for i in vertics:
                index[id] = i
                id = id + 1

        else:
            for i in vertics:
                for j in index.values():
                    if i.x == j.x and i.y == j.y:
                        break
                    elif [j] == index.values()[-1:]:
                        index[id] = i
                        id = id + 1

#check if a already in intersection
def check_repeat(a,intersection):
    if len(intersection) == 0:
        intersection.append(a[0])
        for i in a:
            for j in intersection:
                if i.x == j.x and i.y == j.y:
                    break
                elif [j] == intersection[-1:]:
                    intersection.append(i)     

    else:
        for j in a:
            for i in range(len(intersection)):
                if j.x == intersection[i].x and j.y == intersection[i].y:
                    break       
                elif i == len(intersection) - 1:
                    intersection.append(j)


#check if a already in its intersection list
def get_IAndE(a,my_intersect):
    if len(my_intersect) == 0:
        my_intersect.extend([a])
    else:
        for i in my_intersect:
            if i[0].x == a[0].x and i[0].y == a[0].y:
                for j in a[1:]:
                    for k in i:
                        if j.x == k.x and j.y == k.y:
                            break
                        elif [k] == i[-1:]:
                            i.append(j)
                return my_intersect

            elif [i] == my_intersect[-1:]:
                my_intersect.extend([a])
                return my_intersect
                

def get_intersect(street_line,my_intersect,vertics):
    global index,id
    for i in range(0,len(street_line) - 1):
        for j in street_line[i]:
            for k in range(i+1,len(street_line)):
                for h in street_line[k]:
                    ret = intersect(j,h)

                    if j.dst.y != j.src.y:
                        j_l = j.dst if j.dst.y < j.src.y else j.src
                        j_h = j.src if j.src.y > j.dst.y else j.dst
                    else:
                        j_l = j.dst if j.dst.x < j.src.x else j.src
                        j_h = j.src if j.src.x > j.dst.x else j.dst

                    if ret == 1:
                        if j.dst.y != j.src.y:
                            Exter_l = j.dst if j.dst.y < j.src.y else j.src
                            Exter_h = j.src if j.src.y > j.dst.y else j.dst
                            Inter_l = h.dst if h.dst.y < h.src.y else h.src
                            Inter_h = h.src if h.src.y > h.dst.y else h.dst
                        else:
                            Exter_l = j.dst if j.dst.x < j.src.x else j.src
                            Exter_h = j.src if j.src.x > j.dst.x else j.dst
                            Inter_l = h.dst if h.dst.x < h.src.x else h.src
                            Inter_h = h.src if h.src.x > h.dst.x else h.dst
                                               
                        check_repeat([h.dst,j.dst,h.src,j.src],vertics)
                        get_IAndE([Inter_l,Inter_h,Exter_l],my_intersect)
                        get_IAndE([Inter_h,Inter_l,Exter_h],my_intersect)

                    elif ret == 2:
                        if j.dst.y != j.src.y: 
                            Exter_l = h.dst if h.dst.y < h.src.y else h.src
                            Exter_h = h.src if h.src.y > h.dst.y else h.dst
                            Inter_l = j.dst if j.dst.y < j.src.y else j.src
                            Inter_h = j.src if j.src.y > j.dst.y else j.dst
                        else:
                            Exter_l = h.dst if h.dst.x < h.src.x else h.src
                            Exter_h = h.src if h.src.x > h.dst.x else h.dst
                            Inter_l = j.dst if j.dst.x < j.src.x else j.src
                            Inter_h = j.src if j.src.x > j.dst.x else j.dst

                        check_repeat([h.dst,j.dst,h.src,j.src],vertics)
                        get_IAndE([Inter_l,Inter_h,Exter_l],my_intersect)
                        get_IAndE([Inter_h,Inter_l,Exter_h],my_intersect)
                    
                    elif ret == 3:
                        check_repeat([h.dst,j.dst,h.src,j.src],vertics)
                        get_IAndE([h.src,j_h,j_l],my_intersect)
                        get_IAndE([j_l,h.src,h.dst],my_intersect)
                    
                    elif ret == 4:
                        check_repeat([h.dst,j.dst,h.src,j.src],vertics)
                        get_IAndE([h.src,j_h,j_l],my_intersect)
                        get_IAndE([j_h,h.src,h.dst],my_intersect)
                    
                    elif ret == 5:
                        check_repeat([h.dst,j.dst,h.src,j.src],vertics)
                        get_IAndE([h.dst,j_h,j_l],my_intersect)
                        get_IAndE([j_h,h.src,h.dst],my_intersect)
                    
                    elif ret == 6:
                        check_repeat([h.dst,j.dst,h.src,j.src],vertics)
                        get_IAndE([h.dst,j_h,j_l],my_intersect)
                        get_IAndE([j_l,h.src,h.dst],my_intersect)

                    elif ret == 7:
                        check_repeat([h.dst,h.src],vertics)
                        get_IAndE([h.dst,h.src],my_intersect)

                    elif ret != -1:
                        a =[ret,h.dst,j.dst,h.src,j.src]  
                        check_repeat(a,vertics)
                        get_IAndE(a,my_intersect)

    if(len(vertics)) == 0:
        return -1                                         


def on_sameLine(a,b,c,edge,last_inter,ret):
    if a.x == b.x:
        if c.x == a.x:
            if abs(a.y - c.y) < abs(a.y - b.y) and ((c.y > a.y and b.y > a.y) or (c.y < a.y and b.y < a.y)):
                if abs(a.y - c.y) < abs(a.y - ret[0].y):
                    ret[0] = c
 
    else:
        k = (a.y - b.y)/(a.x - b.x)
        p = a.y - a.x*(a.y - b.y)/(a.x - b.x)
    
        if c.x * k + p - c.y < 0.00001:
            if (a.x - c.x) * (a.x - c.x) + (a.y - c.y) *(a.y - c.y) < (a.x - b.x) * (a.x - b.x) + (a.y - b.y) *(a.y - b.y) and\
            ((c.x > a.x and b.x > a.x) or (c.x < a.x and b.x < a.x)):
                if (a.x - c.x) * (a.x - c.x) + (a.y - c.y) *(a.y - c.y) < (a.x - ret[0].x) * (a.x - ret[0].x) + (a.y - ret[0].y) *(a.y - ret[0].y):
                    ret[0] = c
            

def get_edge(my_intersect,edge,edge_index):
    global index
#get edge
    for i in my_intersect:
        for j in i[1:]:    
            ret = [j]
            for k in range(len(my_intersect)):
                on_sameLine(i[0],j,my_intersect[k][0],edge,my_intersect[-1:][0][0],ret)
            if i[0].x != ret[0].x or i[0].y != ret[0].y:
                edge.extend([[i[0],ret[0]]])  
    my_edge = []
    my_edge.extend([edge[0]])
    
#remove repeated edge
    for i in edge[1:]:
        for j in my_edge:   
            if (i[0].x == j[1].x and i[0].y == j[1].y and i[1].x == j[0].x and i[1].y == j[0].y) or\
            (i[0].x == j[0].x and i[0].y == j[0].y and i[1].x == j[1].x and i[1].y == j[1].y):
                break
            elif [j] == my_edge[-1:]: 
                my_edge.append(i)
                break
 #get index of edge
    for i in my_edge:
        for j in index:
            if index[j].x == i[0].x and index[j].y == i[0].y:
                first = j
                break
        for j in index:
            if index[j].x == i[1].x and index[j].y == i[1].y:
                second = j
                break
        edge_index.extend([[first,second]])


def get_graph(street_line):
    global index
    edge = []
    vertics = []
    my_intersect = []
    edge_index = []
    ret = get_intersect(street_line,my_intersect,vertics)
    if ret == -1:
        return -1
    else:
        get_index(vertics)
        get_edge(my_intersect,edge,edge_index)
        return [[index],edge_index]


def new_get_index(output_edge,value,message):
    for i in range(len(output_edge)):
        if output_edge[i] == message[value]:
            return i



def draw(message):
    if message == -1:
        sys.stdout.write("V 0\n")
        sys.stdout.write("E {}\n")
        sys.stdout.flush()
 
    else:
        output_edge = []
        output_edge = message[0][0].values()
        
        sys.stdout.write("V "+str(len(message[0][0]))+'\n')
        sys.stdout.write("E {")

        for i in message[1]:
            first = new_get_index(output_edge,i[0],message[0][0])
            second = new_get_index(output_edge,i[1],message[0][0])
            sys.stdout.write('<'+str(first)+','+str(second)+'>')
            if [i] != message[1][-1:]:
                sys.stdout.write(",")
        sys.stdout.write("}\n")
        sys.stdout.flush()


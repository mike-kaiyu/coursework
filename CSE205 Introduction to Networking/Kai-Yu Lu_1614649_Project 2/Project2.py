import sys
import os
import multiprocessing
import socket
import time
import operator

nodelist=[]
distancelist=[]
newlist = []
oldlist = []

def server (node, port,nodelist,oldlist):
    PORT = 1000 + nodelist.index(port)
    socketAddress = ('', PORT)
    soc = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    soc.bind(socketAddress)
    soc.listen(5)
    cli,addr = soc.accept()
    result=oldlist[nodelist.index(port)]
    print('Send list:',result)
    sendInfo = ''
    for i in result:
        for j in i:
            if (type(j)==int):
                j = str(j) + '\t'
            elif j == float('inf'):
                j = str(j) + '\t'
            else:
                j += ' '
            sendInfo += j
    cli.sendall(sendInfo.encode('utf-8')) #send note dv table
    soc.close()

def client(node, port,nodelist):
    host = 'localhost'    # The remote host
    PORT = 1000 + nodelist.index(port)    # The same port as used by the server
    time.sleep(2)
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, PORT))
    data = s.recv(1024).decode('UTF-8')
    s.close()
    receinfo_1 = data.split('\t')
    receinfo_2 = []
    for i in receinfo_1:
        if i is '':continue
        n,c = i.split(' ')
        if c == 'inf':
            receinfo_2.append([n,float(c)])
        else:
            receinfo_2.append([n,int(c)])
    print('Receive list: ',receinfo_2)
    return receinfo_2

def TCP(source,neigh,nodelist,oldlist):
    pool = multiprocessing.Pool(2)
    pool.apply_async(server, args = (source, neigh,nodelist,oldlist,))
    retr = pool.apply_async(client, args = (source, neigh,nodelist,))
    pool.close()
    pool.join()
    return retr.get()

def bellman_ford(graph, source,nodelist):
    dist = []
    from_node = []
    to_node = []
    cost = []
    
    for info in graph:
        if len(info)==0: continue
        if info[1] == float('inf'): continue
        from_node.append(info[0][0])
        to_node.append(info[0][2])
        cost.append(info[1])

    max = float('inf')

    for node in nodelist:
        dist.append(max)

    dist[nodelist.index(source)] = 0
    for i in range(len(cost)):
        if cost[i] + dist[nodelist.index(from_node[i])] < dist[nodelist.index(to_node[i])]:
            dist[nodelist.index(to_node[i])] = cost[i] + dist[nodelist.index(from_node[i])]
    result = []
    for i in range(len(dist)):
        result.append([source+'-'+nodelist[i],dist[i]])

    return result

def init():
    global oldlist,newlist
    oldlist = list(list(list() for i in range(len(nodelist))) for i in range(len(nodelist)))
    newlist = list(list(list() for i in range(len(nodelist))) for i in range(len(nodelist)))

    for n in range(len(nodelist)):
        oldlist[n][n] = [nodelist[n] + '-' + nodelist[n], 0]
        newlist[n][n] = [nodelist[n] + '-' + nodelist[n], 0]

    for i in range(len(distancelist)):
        fromn, ton = distancelist[i][0].split('-')
        oldlist[nodelist.index(fromn)][nodelist.index(ton)] = distancelist[i]
        newlist[nodelist.index(fromn)][nodelist.index(ton)] = distancelist[i]

    return newlist,oldlist

def update(nodelist,distancelist):
    global oldlist, newlist
    check_conver = []
    neighbor = []
    init()

    for i in nodelist:
        check_conver.append(False)

    for i in nodelist:
        neighnode = []
        for dis in distancelist:
            nodeinfo = dis[0].split('-')
            if i == nodeinfo[0]:
                neighnode.extend(nodeinfo[1])
        neighbor.append(neighnode)

    for i in neighbor:
        print(i)

    while False in check_conver:
        print('---------------convergence-------------')
        print(check_conver)
        for i in range(len(nodelist)):
            print('---------------node-------------')
            new_graph = []
            source = nodelist[i]
            new_graph.extend(oldlist[nodelist.index(source)])
            for neinode in neighbor[i]:
                receiveInfo = TCP(source, neinode, nodelist, oldlist)
                new_graph.extend(receiveInfo)
            print(new_graph)
            result = bellman_ford(new_graph, source, nodelist)
            newlist[i] = result[:]
        for i in range(len(oldlist)):
            if operator.eq(oldlist[i],newlist[i]):
                check_conver[i] = True
        oldlist = newlist[:]

    for i in range(len(oldlist)):
        output = open('Bellman_node_' + nodelist[i] + '.txt', 'w')
        for j in range(len(oldlist[i])):
            combine, distance = oldlist[i][j]
            node, finish = combine.split('-')
            output.write('Distance from '+node+ ' to '+ finish+' is ' +str(distance) + '\n')
            
        output.close()

def ReadGraph(filename):
    global nodelist,distancelist
    with open(filename, 'r') as file:
        allLine = file.readlines()
    for line in allLine:
        line = line.split('\n')[0]
        if ('Node' in line):
            node= line.replace('Node ', '')
            if (node not in nodelist):
                nodelist.append(node)
            currentnode = node
            # if the line not start with Node

        elif line is not '':
            node, distance = line.split('\t')
            distancelist.append([currentnode+'-'+node,int(distance)])
            distancelist.append([node+'-'+currentnode,int(distance)])
            if (node not in nodelist):
                nodelist.append(node)

    return distancelist,nodelist

def Dij(start,distancelist,nodelist):
    dvlist = []
    unusednode = []
    # list of used nodes
    nodeused = [start]
    for node in nodelist:
        if (node not in nodeused):
            unusednode.append(node)

    # to get list of distance for start node
    for node in nodelist:
        if (node not in nodeused):
            combine = start + '-' + node
            distance = float('+inf')
            for i in range(len(distancelist)):
                if (distancelist[i][0] == combine):
                    distance = distancelist[i][1]
            dvlist.append([node, distance])

    while (unusednode):
        # to find minimum distance
        mindistance = float('+inf')
        minnode = ''
        for i in range(len(dvlist)):
            if (dvlist[i][0] not in nodeused) and (dvlist[i][1] <= mindistance):
                mindistance = dvlist[i][1]
                minnode = dvlist[i][0]

        unusednode.remove(minnode)
        nodeused.append(minnode)

        # the distance list for minnode
        node_dvlist = []
        for node in nodelist:
            if (node != minnode):
                combine = minnode + '-' + node
                distance = float('+inf')
                for i in range(len(distancelist)):
                    if (distancelist[i][0] == combine):
                        distance = distancelist[i][1]
                node_dvlist.append([combine, distance])

        # updating the start node distance list
        for node in nodelist:
            if (node != start) and (node != minnode):
                for i in range(len(dvlist)):
                    if (dvlist[i][0] == node):
                        distance_old = dvlist[i][1]
                    if (dvlist[i][0] == minnode):
                        distance_new1 = dvlist[i][1]

                for i in range(len(node_dvlist)):
                    if (node_dvlist[i][0] == minnode + '-' + node):
                        distance_new2 = node_dvlist[i][1]

                distance_new = distance_new1 + distance_new2
                distance = min(distance_new, distance_old)
                for i in range(len(dvlist)):
                    if (dvlist[i][0] == node):
                        dvlist[i][1] = distance

    output = open('output.txt', 'w')

    for i in range(len(dvlist)):
        print('Distance from ' + start + ' to ' + dvlist[i][0] + ' is ' + str(dvlist[i][1]))
        output.write('Distance from ' + start + ' to ' + dvlist[i][0] + ' is ' + str(dvlist[i][1]) + '\n')

    output.close()

if  __name__ == '__main__':
    filename = sys.argv[1]
    distancelist,nodelist=ReadGraph(filename)

    for i in distancelist:
        print (i)
    if(len(sys.argv)>2):
        start = sys.argv[2]
    else:
        start = nodelist[0]

    Dij(start, distancelist, nodelist)
    update(nodelist,distancelist)
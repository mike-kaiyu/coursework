from socket import *
import os
import re


def graspData(currentHost, currentPath):
    cliSocket =  socket(AF_INET, SOCK_STREAM)
    request = 'GET ' + currentPath +' HTTP/1.1\r\nHost: '+ currentHost +'\r\nConnection: close\r\n\r\n'
    cliSocket.connect((currentHost,port))
    cliSocket.send(request.encode())
    bufStore = []
    while True:
        receive = cliSocket.recv(1024)
        if receive:
            bufStore.append(receive)
        else:
            break
    data = b''.join(bufStore)
    cliSocket.close()
    header, html = data.split(b'\r\n\r\n', 1)
    if '200 OK' not in str(header):
        return ''
    return html


def imageFormat(myData):

    gifURL = r'"([.*\S]*\.gif)"'
    jpgURL = r'"([.*\S]*\.jpg)"'
    pngURL = r'"([.*\S]*\.png)"'
    webpURL = r'"([.*\S]*\.webp)"'
    jpegURL = r'"([.*\S]*\.jpeg)"'

    imageList = re.findall(jpegURL, myData)
    imageList += re.findall(gifURL, myData)
    imageList += re.findall(pngURL, myData)
    imageList += re.findall(webpURL, myData)
    imageList += re.findall(jpgURL,  myData)
    return imageList

def getHref(myData,path):
    hrefs=[]
    hrefStyle = "<a\s[^>]*?href\s*=\s*['\"]([^'\"]*?)['\"][^>]*?>"
    hrefList = re.findall(hrefStyle, myData)
    for item in hrefList:
        if 'http://' in item:
            hrefs.append(item)
        if 'http://' not in item:
            if item[0] == '/':
                item = currentHost + item
            else:
                curPath = currentPath.rstrip()
                item = currentHost + path + item
            hrefs.append(item)
    return hrefs

def storeImage(currentHost, path, imageList, myData):
    for everyName in imageList:
        lastName = everyName.split('/')[-1]

        if  ('http://' not in everyName): # no http
            if (everyName[0] == '/'):
                imageHost = currentHost
                takePath = everyName
                savingPath =currentHost+ path  #name
            else:
                imageHost = currentHost
                takePath = path + everyName
                savingPath =currentHost+ path
        else:
            seperateHTTP = everyName.split('http://')[1] # http:// www.baidu.com/ff/ii/.jpg   to www.baidu.com/ff/ii
            imageHost = seperateHTTP.split('/')[0]  #www.baidu.com
            wholePath = everyName.split(seperateHTTP + imageHost)[1] #/ff/ii/
            name = wholePath.split('/')[-1]

            takePath = wholePath
            savingPath = seperateHTTP

        
        print ('savePath: ',savingPath)
        createFolder(savingPath)
        imgDownload = graspData(imageHost, takePath)
        if imgDownload is not '':
            myfile = open(savingPath + lastName, 'wb')
            myfile.write(imgDownload)
            myfile.close()

def createFolder(href):
    #for href in hrefList:
    if 'http://' in href:
        href = href.split('//')[1]
    existfolder = os.path.exists(href)

    if not existfolder:
        os.makedirs(href)
        print ("the folder is creating... the folder name is:" + href)

    else:
        print("the folder was created before!")

depth  =5

def createdepth(currentHost, currentPath,myData):
    currentDepth = 0
    tempLinks.append("http://" + currentHost +currentPath)
    while currentDepth <= depth:
        links = []
        print('Depth: ',currentDepth)
        while not len(tempLinks) == 0:
            getLink = tempLinks.pop()
            if 'http://' in getLink:
                getLink = getLink.split('http://')[1]
            host = getLink.split('/')[0]
            path = getLink.split(host)[1]
            if path[-1] != '/':
                path = path+'/'
            print('host',host)
            print('path',path)
            data = graspData(host, path)
            if data is not '':
                data = data.decode()
                imagelist = imageFormat(data)
                storeImage(host, path, imagelist, data)
                links.extend(getHref(data,path))
                previousLinks.append(getLink)
        currentDepth += 1
        for link in links:
            if (link != '') & (link not in previousLinks):
                tempLinks.insert(0,link)

   

currentHost = "csse.xjtlu.edu.cn"
currentPath = "/classes/CSE205/"
previousLinks = []
tempLinks = []
port = 80

myData = graspData(currentHost, currentPath).decode() ##decode html
createdepth(currentHost, currentPath, myData)


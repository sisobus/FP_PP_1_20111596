#!/usr/bin/python
#-*- codig: utf-8 -*-
with open('listOfRegister.txt','w') as fp:
    n = 10
    fp.write('%d\n'%n)
    for i in xrange(n):
        fp.write('%012d|12345678|ID%d|05\n'%(i,i))


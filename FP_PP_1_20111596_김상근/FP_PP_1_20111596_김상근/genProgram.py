#!/usr/bin/python
#-*- codig: utf-8 -*-
with open('listOfProgram.txt','w') as fp:
    n = 10
    fp.write('%d\n'%n)
    for i in xrange(n):
        fp.write('ID%d|Swimming|10:10|NAME%d|3\n'%(i,i))


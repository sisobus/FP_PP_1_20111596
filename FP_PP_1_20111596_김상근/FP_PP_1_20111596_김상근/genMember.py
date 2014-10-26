#!/usr/bin/python
#-*- codig: utf-8 -*-
with open('listOfMember.txt','w') as fp:
    n = 10
    fp.write('%d\n'%n)
    for i in xrange(n):
        fp.write('ID%d|PASS%d|ID%s|ID%d@%d.com|ADD%d|1990/05/07|S\n'%(i,i,i,i,i,i))


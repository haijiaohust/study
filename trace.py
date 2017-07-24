# -*- coding:utf-8 -*-
import os
import sys

def convert(file, newfile):
    i = 0
    file_object = open(file, 'r')
    newfile_object = open(newfile, 'w')
    for buf in file_object.readlines():
	u1,u2,u3,u4,u5,u6,u7 = buf.split(',')
	#print buf.split(',')
	#print u1
	if(i == 0):
	    timebase = int(u1)
	i += 1
	if(u4 == 'Write'):
	    type = 'w'
	else:
	    type = 'r'
	time = ("{:.6f}".format(float((int(u1) - timebase) / 10000000.0)))
	new_buf = u3+','+u5+','+u6+','+type+','+time+'\n'
	newfile_object.write(new_buf)
    newfile_object.close()
    file_object.close()

for root, dirs, files in os.walk("."):
    for file in files:
        if(os.path.splitext(file)[1] == '.csv'):
	    newfile=os.path.splitext(file)[0] + '.spc'
	    convert(file, newfile)
	    print file
	    print newfile

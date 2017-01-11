# -*- coding: utf-8 -*-
import hashlib
import os
import sys

if (len(sys.argv) != 2):
    print "argv number error"
    os.exit()

chunks_all = 0
chunks_not_dup = 0
dic = {}
path = sys.argv[1]
def cal_hash(file):
    file_object = open(file, 'rb')
    global chunks_all
    global chunks_not_dup
    try:
        while True:
            chunk = file_object.read(4096)
            if not chunk:
                break
            md5 = hashlib.md5()
            md5.update(chunk)
            md5sum = md5.hexdigest() 
            #print(md5.hexdigest())
            chunks_all+=1
            if (dic.get(md5sum)):
                dic[md5sum]+=1
            else:
                dic[md5sum]=1
                chunks_not_dup+=1
    finally:
        file_object.close()

def list_path(rootdir):
    files = os.listdir(rootdir)
    for file in files:
        cal_hash(os.path.join(rootdir, file))

if os.path.isdir(path):
    list_path(path)
else:
    cal_hash(os.path.join(path))

print("chunks_all: %d chunks_not_dup: %d duprate:%f%%" % (chunks_all, chunks_not_dup, (chunks_all-chunks_not_dup)*1.0/chunks_all*100)) 
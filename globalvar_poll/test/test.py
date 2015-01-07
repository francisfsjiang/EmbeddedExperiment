#!/usr/bin/python3
import ctypes
import sys
def fun(id, num):
    print(id + "  " + num)
    f=open("/dev/globalvar_poll"+id,mode='wb')
    f.raw.write(ctypes.c_uint(int(num)))
    f.close()


if __name__ == "__main__":
    for i in range(1,int(len(sys.argv)/2)+1):
        fun(sys.argv[i*2-1],sys.argv[i*2])
        

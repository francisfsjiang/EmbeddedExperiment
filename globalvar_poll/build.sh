#!/bin/bash

if [ $1 = "build" ]
then
    for ((i=0;i<4;i++))
    do
	echo "num is $i"
	cp globalvar_poll.c globalvar_poll$[i].c
	make num=$i
	sudo insmod globalvar_poll$[i].ko
	sudo mknod /dev/globalvar_poll$[i] c 250 0
    done
elif [ $1 = "clean" ]
then
    make clean
    for ((i=0;i<4;i++))
    do
	echo "num is $i"
	rm globalvar_poll$[i].c
	sudo rmmod globalvar_poll$[i].ko
	sudo rm /dev/globalvar_poll$[i]
    done
fi

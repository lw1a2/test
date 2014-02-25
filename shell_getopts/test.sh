#!/bin/bash

usage() {
    prog=`basename $0`
    echo "Usage: $prog <options>"
    echo "Options:"
    echo "    -a 			echo aaa"
	echo "    -b 			echo bbb"
	echo "    -c <arg>		echo arg"
    echo "    -h			display this help and exit"
    exit
}

while getopts "abc:h" Option	#这个while似乎不能放到函数里
do
    case $Option in
        a) echo "aaa";;		#无参数的
        b) echo "bbb";;		#无参数的
        c) echo "$OPTARG";;	#有参数的
		h) usage;;			#帮助
        *) usage;;			#如果参数输入有误，则打印完shell的错误后，会执行这里
    esac
done


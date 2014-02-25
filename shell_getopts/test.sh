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

while getopts "abc:h" Option	#���while�ƺ����ܷŵ�������
do
    case $Option in
        a) echo "aaa";;		#�޲�����
        b) echo "bbb";;		#�޲�����
        c) echo "$OPTARG";;	#�в�����
		h) usage;;			#����
        *) usage;;			#������������������ӡ��shell�Ĵ���󣬻�ִ������
    esac
done


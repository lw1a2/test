#!/bin/bash

PASSWD=admin

#while [ -n $PASSWD ]
#do
#    echo $PASSWD
    RET=`curl --basic -u admin:${PASSWD} http://192.168.1.1 2>&1|grep 401|wc -l`
    echo $RET
    if [ ${RET} != 1 ]
    then
	echo $PASSWD
	echo 'OK'
    fi
#    PASSWD=''
#done


#!/bin/bash

retries=5
i=0
while [ $i -lt $retries ]
do
    echo $i
    i=$(( $i + 1 ))
    sleep 1
done
#1/bin/bash

rm -f tmp.txt
i=0
total_time=0
run_times=100
while [ ${i} -lt ${run_times} ]
do
    single_time=`$1`
    i=`expr ${i} + 1`
    total_time=$((${total_time}+${single_time}))
done

#echo `expr ${total_time} / ${run_times}`
echo $((${total_time}/${run_times}))


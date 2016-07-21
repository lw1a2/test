#!/bin/bash

Location="WAC"
Year="16"
Day="145"
StartNumber=1
EndNumber=2
DATETIME=`date +%Y%m%d%H%M`
OutputFile="h1b_check_status.${DATETIME}.out"

StartCaseNumerPre=${Location}${Year}${Day}5
SNWidth=4

rm -f ${OutputFile}
for (( I=${StartNumber}; I<=${EndNumber}; I++ ))
do
	ZERO=""
	WidthOfI=`echo -n ${I}|wc -c`
	for (( J=${WidthOfI}; J<${SNWidth}; J++ ))
	do
		ZERO=${ZERO}0
	done
	CaseNumber=${StartCaseNumerPre}${ZERO}${I}
	
	echo -n -e ${CaseNumber}: "\t" | tee -a ${OutputFile}
	
	curl -k --data "changeLocale=&completedActionsCurrentPage=0&upcomingActionsCurrentPage=0&appReceiptNum=${CaseNumber}&caseStatusSearchBtn=CHECK+STATUS" https://egov.uscis.gov/casestatus/mycasestatus.do -o /tmp/h1b_check_status.$$.out 2>/dev/null
	
	Status=`grep -C 1 "Your Current Status:" /tmp/h1b_check_status.$$.out|tail -1|sed -e 's/^[[:space:]]*//'`
	echo ${Status} | tee -a ${OutputFile}
done

echo =========================================================================== | tee -a ${OutputFile}
grep -v ==== ${OutputFile} | awk -F '\t' '{print $2}' | sort | uniq -c | tee -a ${OutputFile}

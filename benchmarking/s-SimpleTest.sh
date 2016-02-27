#!/bin/bash
OUTFILE="results/ib_send_results.txt"
INTF="tnvme40Gp1"
IB_SEND_BW="ib_send_bw $INTF --report_gbits"

echo "" > $OUTFILE

COUNTER=1
while [  $COUNTER -lt 5 ]; do
    $( $IB_SEND_BW 2>&1 | grep "Gb/s" -A 1 &>> $OUTFILE )

    let COUNTER=COUNTER+1 
done

#!/bin/bash
IB_SEND_BW="ib_send_bw --report_gbits"

COUNTER=0
UPPER_BOUND=20
while [ $COUNTER -lt $UPPER_BOUND ]; do
    $IB_SEND_BW &> /dev/null

    let COUNTER=COUNTER+1
done

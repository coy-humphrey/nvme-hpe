#!/bin/bash
IB_SEND_BW="ib_send_bw --report_gbits"

COUNTER=1
while [ $COUNTER -lt 5  ]; do
    $IB_SEND_BW &> /dev/null

    let COUNTER=COUNTER+1
done

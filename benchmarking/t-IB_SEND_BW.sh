#!/bin/bash

# START of variables to modify

IB_SEND_BW="ib_send_bw --report_gbits"

NUM_RUNS=20

# END of variables to modify

COUNTER=0
while [ $COUNTER -lt $NUM_RUNS ]; do
    $IB_SEND_BW &> /dev/null

    let COUNTER=COUNTER+1
done

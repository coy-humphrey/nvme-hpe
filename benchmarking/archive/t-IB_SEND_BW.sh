#!/bin/bash

# START of variables to modify

MAIN_COMMAND="ib_send_bw --report_gbits"

NUM_RUNS=20

# END of variables to modify

COUNTER=0
while [ $COUNTER -lt $NUM_RUNS ]; do
    $MAIN_COMMAND &> /dev/null

    let COUNTER=COUNTER+1
done

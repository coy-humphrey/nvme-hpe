#!/bin/bash

# START of variables to modify

OUTFILE="results/ib_send_bw_results.txt"

INTF="tnvme40Gp1"
MAIN_COMMAND="ib_send_bw $INTF --report_gbits"

KEYWORD_1="Gb/s"
KEYWORD_2="\"Send BW Test\""
GREP_0="grep $KEYWORD_2 -B 1 -A 19"
GREP_1="grep $KEYWORD_1 -A 1"
GREP_2="$GREP_1 | grep $KEYWORD_1 -v"

OUT_COMMAND_PRELUDE="$MAIN_COMMAND 2>&1 | $GREP_0 &>> $OUTFILE"
OUT_COMMAND="$MAIN_COMMAND 2>&1 | $GREP_2 &>> $OUTFILE"

NUM_RUNS=20

# END of variables to modify

rm $OUTFILE 2> /dev/null

COUNTER=0
while [  $COUNTER -lt $NUM_RUNS ]; do
    if [ $COUNTER = 0 ]; then
        eval "$OUT_COMMAND_PRELUDE"
    else
        eval "$OUT_COMMAND"        
    fi

    let COUNTER=COUNTER+1 
done

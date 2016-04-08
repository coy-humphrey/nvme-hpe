#!/bin/bash

python run_all_t.py 2> errors/stderr-t.txt
DIR=`ls -d errors/*/ | cat | tail -n 1`
mv errors/stderr-t.txt "$DIR"

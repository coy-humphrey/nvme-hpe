#!/bin/bash

python run_all_s.py 2> errors/stderr-s.txt
DIR=`ls -d errors/*/ | cat | tail -n 1`
mv errors/stderr-s.txt "$DIR"

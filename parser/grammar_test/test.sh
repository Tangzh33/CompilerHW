#!/bin/bash
#rm *.log *.output *.c
cp ../parser.y .
bison parser.y -v -Wcounterexamples 2>&1 | tee examples.log
# bison parser.y -v -Wcounterexamples 2>&1 | tee -a examples.log
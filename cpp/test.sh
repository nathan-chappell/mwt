#!/bin/bash

vcone1="2
1 0
0 1"

vcone2="3
1 0 0
0 1 0
0 0 1
"

vcone3="2
0 1
1 1
"

vcone4="3
1 1 0
0 1 1
1 0 1
0 1 1
"

vcones=( vcone{1..3} )

run_test() {
  echo "testing: $2"
  echo "$1"
  echo "-------"
  echo "$1" | ./main $2
}

for cone in ${vcones[@]}; do
  run_test "${!cone}" "-VC"
done

#!/bin/bash

vcone1="2
1 0
0 1"

vcone2="3
1 0 0
0 1 0
0 0 1"

vcone3="2
0 1
1 1"

vcone4="3
1 1 0
0 1 1
1 0 1
0 1 1"

vcones=( vcone{1..4} )

test_vcone() {
  echo "testing: vcone_to_hcone"
  echo "$1"
  echo "-------"
  echo "$1" | ./vcone_to_hcone
  echo "----------------------------"
}

for cone in ${vcones[@]}; do
  test_vcone "${!cone}"
done

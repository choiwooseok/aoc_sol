#! /bin/bash

EXPECTED_ARGS=1

if [ "$#" -ne "$EXPECTED_ARGS" ]; then
  echo "Usage: $0 <day#>"
  exit 1 # Exit with an error code
fi

day="$1"

g++ $day/$day.cpp -std=c++20

./a.out
rm -rf ./a.out

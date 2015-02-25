#!/bin/bash

# local descent
echo "==== local descent ===="
time ./meta.out --file data/specification.md --heuristic ld

# local search
echo "==== local search ===="
time ./meta.out --file data/specification.md --heuristic ls

# tabu search
#echo "==== tabu search ===="
#time ./meta.out --file data/specification.md --heuristic ts
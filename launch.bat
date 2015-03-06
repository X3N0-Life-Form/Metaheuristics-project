# local descent
echo "==== local descent ===="
time ./meta.exe --file data/specification.md --heuristic ld

# local search
echo "==== local search ===="
time ./meta.exe --file data/specification.md --heuristic ls

# tabu search
echo "==== tabu search ===="
time ./meta.exe --file data/specification.md --heuristic ts
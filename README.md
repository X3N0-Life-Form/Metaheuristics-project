# Metaheuristics-project
Apply a meta-heuristic to a problem.

## Compilation
Call `cmake` in the root folder.
`make` ==> meta.out


## Launch options
* *--file [file path]*: specify a file to parse
* *--heuristic [heuristic type]*: specify a heuristic to use
    * *ld* : Best Fit local descent
    * *ls* : probabilistic Local Search
    * *ts* : Tabu Search
* *--periods [number]* : specify a number of periods

## Example:
* `./meta.out --file data/specification.md --periods 4 --heuristic ls`

*or*

* `./launch.sh`
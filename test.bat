testgen.exe -N=400 -K=200 -F=test -Q=1 > NUL
convert.exe test.graph test.satinput > NUL
minisat test.satinput test.satoutput
revert.exe test.satoutput test.graph test.subgraphs
python checker.py .\test.graph .\test.subgraphs
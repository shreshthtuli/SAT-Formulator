testgen.exe -N=100 -K=20 -F=test -Q=1 > NUL
convert.exe test.graph test.satinput
minisat test.satinput test.satoutput > NUL
revert.exe test.satoutput test.graph test.subgraphs
python checker.py .\test.graph .\test.subgraphs
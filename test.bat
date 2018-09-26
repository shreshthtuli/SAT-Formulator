testgen.exe -N=20 -K=7 -F=test -Q=1 > NUL
convert.exe test.graph test.satinput > NUL
minisat test.satinput test.satoutput > NUL
revert.exe test.satoutput test.graph test.subgraphs > NUL
python checker.py .\test.graph .\test.subgraphs
REM testgen -N=200 -K=50 -F=test -Q=1 
python problemGenerator.py 5 2
conv.exe test.graph test.satinput
minisat test.satinput test.satoutput
rev.exe test.satoutput test.graph test.subgraphs
python checker.py test.graph test.subgraphs

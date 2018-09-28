testgen -N=100 -K=5 -F=test -Q=1 -U=1
conv.exe test.graph test.satinput
minisat test.satinput test.satoutput
rev.exe test.satoutput test.graph test.subgraphs
python checker.py test.graph test.subgraphs

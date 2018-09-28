conv.exe ./jumbotest.graph test.satinput
minisat test.satinput test.satoutput
rev.exe test.satoutput ./jumbotest.graph test.subgraphs

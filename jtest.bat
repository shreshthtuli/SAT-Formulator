conv.exe ./Testcases/jumbotest.graph test.satinput
minisat test.satinput test.satoutput
rev.exe test.satoutput ./Testcases/jumbotest.graph test.subgraphs

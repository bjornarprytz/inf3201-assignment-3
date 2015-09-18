Assignment 2 README
===================

The presentations are found in Assignment 2 and OpenMP PDF/ODP files.
Requirements are found in the Assignment 2 presentation.

markovian
---------
Markovian can be found at https://github.com/naftaliharris/markovian/

The benchmark code can be found in the learn/speedbenchmark/ subdirectory.
When using the benchmark to profile and test, I suggest using a subset of the speedbenchmark.fens/.plies files, e.g. by doing:
head -n 5 speedbenchmark.fens > short.fens
head -n 5 speedbenchmark.plies > short.plies
make
./a.out --fen-file short.fens --ply-file short.plies


ompP
----

ompP can be found at http://www.ompp-tool.com

Installation instructions are in the INSTALL file.

To use ompP, prepend your compiler call with the kinst-ompp script, then run the program. Your output will be in a .txt file.

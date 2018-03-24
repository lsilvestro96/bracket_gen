# NCAA March Madness bracket generator
This is a simple c++11 program to generate a March Madness Bracket.
## Input
This program takes 2 command-line arguments: an input file formatted with a list of teams and their seeds,

and the name of a file to output the results. A sample input file is included in the "data" directory.
## Building/Running
This program needs to be compiled with c++11 support. For example:

```$ g++ -std=c++11 -Wall main.cpp team.cpp -o bracket_gen.out```

To run the program, supply it with the input and output file to use:

```$ ./bracket_gen.out data/ex_in.txt data/ex_out.txt```
 

load "mixedMult.m2";

problem=newProblem(18, 3,{5, 6, 6, 6, 6, 6, 6, 6, 6});
<<" Degree 18 Multiplicities: 3:1 5:1 6:8  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(19, 3,{6, 6, 6, 6, 6, 6, 6, 7, 7});
<<" Degree 19 Multiplicities: 3:1 6:7 7:2  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(20, 3,{6, 6, 6, 6, 7, 7, 7, 7, 7});
<<" Degree 20 Multiplicities: 3:1 6:4 7:5  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(21, 3,{6, 7, 7, 7, 7, 7, 7, 7, 7});
<<" Degree 21 Multiplicities: 3:1 6:1 7:8  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(21, 3,{6, 6, 7, 7, 7, 7, 7, 7, 8});
<<" Degree 21 Multiplicities: 3:1 6:2 7:6 8:1  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(22, 5,{7, 7, 7, 7, 7, 7, 7, 7, 8});
<<" Degree 22 Multiplicities: 5:1 7:8 8:1  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(22, 3,{7, 7, 7, 7, 7, 7, 7, 8, 8});
<<" Degree 22 Multiplicities: 3:1 7:7 8:2  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(22, 3,{6, 7, 7, 7, 7, 7, 8, 8, 8});
<<" Degree 22 Multiplicities: 3:1 6:1 7:5 8:3  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(23, 5,{7, 7, 7, 7, 7, 8, 8, 8, 8});
<<" Degree 23 Multiplicities: 5:1 7:5 8:4  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(23, 3,{7, 7, 7, 7, 8, 8, 8, 8, 8});
<<" Degree 23 Multiplicities: 3:1 7:4 8:5  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(23, 3,{6, 7, 7, 8, 8, 8, 8, 8, 8});
<<" Degree 23 Multiplicities: 3:1 6:1 7:2 8:6  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(24, 5,{7, 7, 8, 8, 8, 8, 8, 8, 8});
<<" Degree 24 Multiplicities: 5:1 7:2 8:7  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(24, 5,{6, 8, 8, 8, 8, 8, 8, 8, 8});
<<" Degree 24 Multiplicities: 5:1 6:1 8:8  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(24, 3,{7, 8, 8, 8, 8, 8, 8, 8, 8});
<<" Degree 24 Multiplicities: 3:1 7:1 8:8  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(22, 3,{7, 7, 7, 7, 7, 7, 7, 7, 9});
<<" Degree 22 Multiplicities: 3:1 7:8 9:1  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(23, 3,{7, 7, 7, 7, 7, 8, 8, 8, 9});
<<" Degree 23 Multiplicities: 3:1 7:5 8:3 9:1  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(24, 5,{7, 7, 7, 8, 8, 8, 8, 8, 9});
<<" Degree 24 Multiplicities: 5:1 7:3 8:5 9:1  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(24, 3,{7, 7, 8, 8, 8, 8, 8, 8, 9});
<<" Degree 24 Multiplicities: 3:1 7:2 8:6 9:1  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(24, 3,{6, 8, 8, 8, 8, 8, 8, 8, 9});
<<" Degree 24 Multiplicities: 3:1 6:1 8:7 9:1  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(25, 5,{8, 8, 8, 8, 8, 8, 8, 8, 9});
<<" Degree 25 Multiplicities: 5:1 8:8 9:1  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(24, 3,{7, 7, 7, 8, 8, 8, 8, 9, 9});
<<" Degree 24 Multiplicities: 3:1 7:3 8:4 9:2  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(25, 5,{7, 8, 8, 8, 8, 8, 8, 9, 9});
<<" Degree 25 Multiplicities: 5:1 7:1 8:6 9:2  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(25, 3,{8, 8, 8, 8, 8, 8, 8, 9, 9});
<<" Degree 25 Multiplicities: 3:1 8:7 9:2  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(25, 5,{7, 7, 8, 8, 8, 8, 9, 9, 9});
<<" Degree 25 Multiplicities: 5:1 7:2 8:4 9:3  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(25, 3,{7, 8, 8, 8, 8, 8, 9, 9, 9});
<<" Degree 25 Multiplicities: 3:1 7:1 8:5 9:3  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(25, 3,{7, 7, 8, 8, 8, 9, 9, 9, 9});
<<" Degree 25 Multiplicities: 3:1 7:2 8:3 9:4  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(26, 5,{8, 8, 8, 8, 8, 9, 9, 9, 9});
<<" Degree 26 Multiplicities: 5:1 8:5 9:4  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(26, 5,{7, 8, 8, 8, 9, 9, 9, 9, 9});
<<" Degree 26 Multiplicities: 5:1 7:1 8:3 9:5  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(26, 3,{8, 8, 8, 8, 9, 9, 9, 9, 9});
<<" Degree 26 Multiplicities: 3:1 8:4 9:5  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(26, 5,{7, 7, 8, 9, 9, 9, 9, 9, 9});
<<" Degree 26 Multiplicities: 5:1 7:2 8:1 9:6  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(26, 3,{7, 8, 8, 9, 9, 9, 9, 9, 9});
<<" Degree 26 Multiplicities: 3:1 7:1 8:2 9:6  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(26, 3,{7, 7, 9, 9, 9, 9, 9, 9, 9});
<<" Degree 26 Multiplicities: 3:1 7:2 9:7  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(27, 5,{8, 8, 9, 9, 9, 9, 9, 9, 9});
<<" Degree 27 Multiplicities: 5:1 8:2 9:7  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(27, 5,{7, 9, 9, 9, 9, 9, 9, 9, 9});
<<" Degree 27 Multiplicities: 5:1 7:1 9:8  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(27, 3,{8, 9, 9, 9, 9, 9, 9, 9, 9});
<<" Degree 27 Multiplicities: 3:1 8:1 9:8  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(28, 7,{9, 9, 9, 9, 9, 9, 9, 9, 9});
<<" Degree 28 Multiplicities: 7:1 9:9  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(25, 5,{7, 8, 8, 8, 8, 8, 8, 8, 10});
<<" Degree 25 Multiplicities: 5:1 7:1 8:7 10:1  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(25, 3,{8, 8, 8, 8, 8, 8, 8, 8, 10});
<<" Degree 25 Multiplicities: 3:1 8:8 10:1  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(25, 3,{7, 8, 8, 8, 8, 8, 8, 9, 10});
<<" Degree 25 Multiplicities: 3:1 7:1 8:6 9:1 10:1  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(26, 5,{8, 8, 8, 8, 8, 8, 9, 9, 10});
<<" Degree 26 Multiplicities: 5:1 8:6 9:2 10:1  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(26, 5,{7, 8, 8, 8, 8, 9, 9, 9, 10});
<<" Degree 26 Multiplicities: 5:1 7:1 8:4 9:3 10:1  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(26, 3,{8, 8, 8, 8, 8, 9, 9, 9, 10});
<<" Degree 26 Multiplicities: 3:1 8:5 9:3 10:1  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(26, 3,{7, 8, 8, 8, 9, 9, 9, 9, 10});
<<" Degree 26 Multiplicities: 3:1 7:1 8:3 9:4 10:1  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(27, 5,{8, 8, 8, 9, 9, 9, 9, 9, 10});
<<" Degree 27 Multiplicities: 5:1 8:3 9:5 10:1  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(27, 5,{7, 8, 9, 9, 9, 9, 9, 9, 10});
<<" Degree 27 Multiplicities: 5:1 7:1 8:1 9:6 10:1  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(27, 3,{8, 8, 9, 9, 9, 9, 9, 9, 10});
<<" Degree 27 Multiplicities: 3:1 8:2 9:6 10:1  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(27, 3,{7, 9, 9, 9, 9, 9, 9, 9, 10});
<<" Degree 27 Multiplicities: 3:1 7:1 9:7 10:1  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(28, 7,{8, 9, 9, 9, 9, 9, 9, 9, 10});
<<" Degree 28 Multiplicities: 7:1 8:1 9:7 10:1  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(28, 5,{9, 9, 9, 9, 9, 9, 9, 9, 10});
<<" Degree 28 Multiplicities: 5:1 9:8 10:1  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;
problem=newProblem(26, 5,{8, 8, 8, 8, 8, 8, 8, 10, 10});
<<" Degree 26 Multiplicities: 5:1 8:7 10:2  dimension:"<<(expDim problem)<<" 2k+1:"<<2*(k problem) +1<< " -> "<<checkConjecture(problem) <<endl;

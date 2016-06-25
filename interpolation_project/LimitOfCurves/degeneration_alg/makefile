#

AlignSing.o: AlignSing.h exceptions.h AlignSing.cpp
	g++ -c AlignSing.cpp -O2

AlignIdeal.o: AlignIdeal.h exceptions.h AlignIdeal.cpp
	g++ -c AlignIdeal.cpp -O2

InterProblem.o: InterProblem.cpp InterProblem.h
	g++ -c InterProblem.cpp -O2

blownupprojplane.o: blownupprojplane.h blownupprojplane.cpp
	g++ -c blownupprojplane.cpp -O2

baseLocus.o: baseLocus.h baseLocus.cpp
	g++ -c baseLocus.cpp -O2

tool: degTool.cpp InterProblem.o AlignIdeal.o AlignSing.o blownupprojplane.o baseLocus.o
	g++ -o degtool degTool.cpp InterProblem.o AlignIdeal.o AlignSing.o blownupprojplane.o baseLocus.o -lglpk -O2

testAlignSing: AlignSing.o test/testAlignSing.cpp
	g++ -o test/testAlignSing test/testAlignSing.cpp AlignSing.o 

testAlignIdeal: AlignSing.o AlignIdeal.o test/testAlignIdeal.cpp
	g++ -o test/testAlignIdeal test/testAlignIdeal.cpp AlignSing.o AlignIdeal.o 

testInterProblem: InterProblem.o AlignSing.o AlignIdeal.o
	g++ -o test/testInterProblem test/testInterProblem.cpp InterProblem.o AlignSing.o AlignIdeal.o

testblownupprojplane: blownupprojplane.o test/testblownupprojplane.cpp
	g++ -o test/testblownupprojplane test/testblownupprojplane.cpp blownupprojplane.o

test: testAlignSing testAlignIdeal testInterProblem testblownupprojplane
	./test/testAlignSing
	./test/testAlignIdeal
	./test/testInterProblem
	./test/testblownupprojplane

clean: 
	rm *.o

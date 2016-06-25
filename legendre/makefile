primetable.o: primetable.h primetable.cpp
	g++ -c primetable.cpp -O2

factor.o: primepower.h factor.h factor.cpp
	g++ -c factor.cpp -O2

legendre.o: legendre.h primepower.h legendre.cpp
	g++ -c legendre.cpp -O2

tool: tool.cpp hilbert.o primetable.o factor.o legendre.o
	g++ -o tool tool.cpp hilbert.o primetable.o factor.o legendre.o

hilbert.o: hilbert.cpp hilbert.h primetable.h
	g++ -c hilbert.cpp -O2

primetabletest: primetable.o test/primetabletest.cpp
	g++ -o test/primetabletest test/primetabletest.cpp primetable.o

factortest: test/factortest.cpp factor.o primetable.o
	g++ -o test/factortest test/factortest.cpp factor.o primetable.o

legendretest: test/legendretest.cpp legendre.o factor.o primetable.o
	g++ -o test/legendretest test/legendretest.cpp legendre.o factor.o primetable.o

hilberttest: test/hilberttest.cpp hilbert.o primetable.o factor.o legendre.o
	g++ -o test/hilberttest test/hilberttest.cpp hilbert.o primetable.o factor.o legendre.o

test: primetabletest factortest legendretest hilberttest
	./test/primetabletest
	./test/factortest
	./test/legendretest
	./test/hilberttest

clean:
	rm *.o
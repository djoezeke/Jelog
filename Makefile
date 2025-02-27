all : compile build run

compile:
	g++ -c Sample/sample.cpp -IJe-Log 

build:
	g++ sample.o -IJe-Log/ -o sample 

run:
	./sample.exe

clean:
	rm -f sampel.o
	rm -f sampel.exe

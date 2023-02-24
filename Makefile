all: oss worker

oss:
	g++ -o ./oss ./oss.cpp
worker:
	g++ -o ./worker ./worker.cpp
clean:
	rm -f ./oss ./worker

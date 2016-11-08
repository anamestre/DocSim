DocSim2.x: DocSim2.o JaccApprox.o
	g++ -o DocSim2.x DocSim2.o JaccApprox.o

JaccApprox.o: JaccApprox.hh JaccApprox.cc
	g++ -c JaccApprox.cc -std=c++11

DocSim2.o: DocSim2.cc
	g++ -c DocSim2.cc -std=c++11

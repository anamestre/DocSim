DocSimMain.x: DocSimMain.o JaccApprox.o
	g++ -o DocSimMain.x DocSimMain.o JaccApprox.o

JaccApprox.o: JaccApprox.hh JaccApprox.cc
	g++ -c JaccApprox.cc -std=c++11

DocSimMain.o: DocSimMain.cc
	g++ -c DocSimMain.cc -std=c++11

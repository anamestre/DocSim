DocSimMain.x: DocSimMain.o JaccApprox.o LocalitySensitive.o
	g++ -o DocSimMain.x DocSimMain.o JaccApprox.o LocalitySensitive.o

JaccApprox.o: JaccApprox.hh JaccApprox.cc
	g++ -c JaccApprox.cc -std=c++11

DocSimMain.o: DocSimMain.cc
	g++ -c DocSimMain.cc -std=c++11

LocalitySensitive.o: LocalitySensitive.hh LocalitySensitive.cc
	g++ -c LocalitySensitive.cc -std=c++11

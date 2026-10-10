CXX = g++
CFLAG = $(shell mysql_config --libs)


testMySQL: main.cpp bin/bddServeur.cpp bin/bddServeur.h
	$(CXX) bin/bddServeur.h bin/bddServeur.cpp main.cpp $(CFLAG) -o testMySQL

testSocket: main.cpp bin/sockClient.cpp bin/sockClient.h
	$(CXX) bin/sockClient.h bin/sockClient.cpp main.cpp -o testSocket

testAll:
	$(CXX) bin/* recieve_data/main.cpp $(CFLAG) -o testAll

testModule:
	$(CXX) bin/*.h bin/*.cpp main.cpp $(CFLAG) -o testModule

testpompe: 
	$(CXX) bin/bddServeur.* recuperation_eau/recuperation_eau.cpp $(CFLAG) -o testpompe -lwiringPi
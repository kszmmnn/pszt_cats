.DEFAULT_GOAL := all
.PHONY : clean

SRC_DIR := ./src
INC_DIR := ./inc
CFLAGS := -Wall -Wextra -pedantic -std=c++17 -Iinc



filereader.o: $(INC_DIR)/FileReader.h $(SRC_DIR)/FileReader.cpp
	g++ $(CFLAGS) -c $(SRC_DIR)/FileReader.cpp -o filereader.o

randomnumber.o: $(INC_DIR)/RandomNumber.h $(SRC_DIR)/RandomNumber.cpp
	g++ $(CFLAGS) -c $(SRC_DIR)/RandomNumber.cpp -o randomnumber.o

neuron.o: $(INC_DIR)/Neuron.h $(SRC_DIR)/Neuron.cpp randomnumber.o
	g++ $(CFLAGS) -c $(SRC_DIR)/Neuron.cpp -o neuron.o

layer.o: $(INC_DIR)/Layer.h $(SRC_DIR)/Layer.cpp neuron.o
	g++ $(CFLAGS) -c $(SRC_DIR)/Layer.cpp -o layer.o

network.o: $(INC_DIR)/Network.h $(SRC_DIR)/Network.cpp layer.o
	g++ $(CFLAGS) -c $(SRC_DIR)/Network.cpp -o network.o


main.o: $(SRC_DIR)/main.cpp filereader.o network.o
	g++ $(CFLAGS) -c  $(SRC_DIR)/main.cpp -o main.o

pszt_cats: main.o
	g++ -o pszt-cats main.o network.o filereader.o layer.o neuron.o randomnumber.o

all: pszt_cats

clean:
	-rm *.o pszt-cats
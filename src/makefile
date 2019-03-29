

CC = g++ -std=c++11
CC_FLAGES = -O3 -fopenmp
HEAD_FILES = Interpolate.h GridIO.h Divide.h Form.h
OBJS  = GridIO.o Interpolate.o Divide.o main.o
.PHONY: Inter clean test

Inter : $(OBJS) $(HEAD_FILES) 
	$(CC) $(CC_FLAGES)  $(OBJS) -o Inter
GridIO.o : GridIO.h GridIO.cpp
	$(CC) -c GridIO.cpp

Divide.o : Divide.h Divide.cpp
	$(CC) -c Divide.cpp

Interpolate.o : Interpolate.cpp Interpolate.h
	$(CC) $(CC_FLAGES) -c Interpolate.cpp

main.o : main.cpp 
	$(CC) $(CC_FLAGES) -c main.cpp

test:
	nohup ./Inter &
clean:
	rm -f *.o *.gch
	rm Inter
	rm de.txt


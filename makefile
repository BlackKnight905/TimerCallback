CC = g++
TARGET = demo
INC_PATH = $(PWD)/inc
SRC_PATH = $(PWD)/src
CFLAGS = -O2 -I $(INC_PATH) -Wall -lpthread
OBJS = $(TARGET).o timer.o timerCallback.o


all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)
	./$(TARGET)

$(TARGET).o : $(TARGET).cpp
	$(CC) $(CFLAGS) -c $(TARGET).cpp

timer.o : $(SRC_PATH)/timer.cpp
	$(CC) $(CFLAGS) -c $(SRC_PATH)/timer.cpp

timerCallback.o : $(SRC_PATH)/timerCallback.cpp
	$(CC) $(CFLAGS) -c $(SRC_PATH)/timerCallback.cpp

clean:
	rm *.o $(TARGET)


TARGET = prog
SRC = main.cpp

default:
	@g++ -o $(TARGET) $(SRC)

clean:
	@rm $(TARGET)

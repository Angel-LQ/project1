INC_DIR:= ../Include/
SRC_DIR:= ./
CC:=g++
CPPFLAGS:= -std=c++11 -g
LIBS:= -lpthread
INC_FILE:= $(addprefix -I, $(INC_DIR))
SRC_FILE:= $(wildcard ./*.cc )
TARGET:=../Bin/Client.exe

$(TARGET):$(SRC_FILE)
	$(CC) -o $@ $^ $(CPPFLAGS) $(INC_FILE) $(LIBS)

clean:
	rm -rf $(TARGET)

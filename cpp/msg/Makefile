
SRC_DIR=src
BUILD_DIR=obj
TARGET_DIR=bin
LIB=

CC=g++
CFLAGS=-g -std=c++11

## Find all source file automatically
## this will make SRC equal to "src/serv_main.cpp src/server.cpp ..."
SRC=$(shell find $(SRC_DIR) -type f -name *.cpp)

## make OBJ = to SRC where you substiture BUILD_DIR for SRC_DIR and .cpp for .o:
## so OBJ something like "obj/serv_main.o obj/server.o ..."
OBJ=$(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SRC:.cpp=.o))

## make DEPS (dependencies) equal to OBJS where you replace .o by .d
## so DEPS something like "obj/serv_main.d obj/server.d"
DEPS=$(OBJ:%.o=%.d)

## first rule is the one by default, makes everything
all: directories $(TARGET_DIR)/serv

## create the directory you need (obj and bin)
directories:
	@mkdir -p $(TARGET_DIR)
	@mkdir -p $(BUILD_DIR)

## "make clean": deletes everything to rebuild everything. PHONY means it does not create any files
.PHONY: depend
clean:
	rm -fr $(BUILD_DIR)
	rm -fr $(TARGET_DIR)

-include $(DEPS)
$(TARGET_DIR)/serv: $(OBJ)
	$(CC) -o $@ $^ $(LIB)

## "make depend" will force creation of all the .d files
## the .d file contains for each cpp fiel what .h it depends on
.PHONY: depend
depend: $(DEPS)	

## The compilation rule: How do you make a %.o from a %.cpp
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

## How to make the .d files from a .cpp (-MM is an option of gcc that does that)
$(BUILD_DIR)/%.d: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -MM -MF $@ $<

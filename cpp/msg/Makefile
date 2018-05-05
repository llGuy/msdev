SRC_DIR=src
BUILD_DIR=obj
TARGET_DIR=bin
LIB=

CC=g++
CFLAGS=-g -std=c++1z

SRC=$(shell find $(SRC_DIR) -type f -name *.cpp)
OBJ=$(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SRC:.cpp=.o))
DEPS=$(OBJ:%.o=%.d)

all: directories $(TARGET_DIR)/serv

directories:
	@mkdir -p $(TARGET_DIR)
	@mkdir -p $(BUILD_DIR)

clean:
	rm -fr $(BUILD_DIR)
	rm -fr $(TARGET_DIR)

-include $(DEPS)
$(TARGET_DIR)/serv: $(OBJ)
	$(CC) -o $@ $^ $(LIB)

depend: $(DEPS)	

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILD_DIR)/%.d: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -MM -MF $@ $<

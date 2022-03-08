.PHONY: all build clean debug info test

CC      = gcc
CFLAGS  = -std=c++17 -Wall -Werror
LDFLAGS = -Llib -lstdc++ -lsqlite3 -lpthread -ldl
INCLUDE = -Iinclude/

BUILD   = ./build
OBJ_DIR = $(BUILD)/objects
APP_DIR = $(BUILD)/apps
SRC     = $(wildcard src/*.cpp) \
		  $(wildcard src/**/*.cpp)

OBJECTS = $(SRC:%.cpp=$(OBJ_DIR)/%.o)
TARGET  = aletheia

TEST_SRC = $(wildcard test/*.cpp) \
		   $(wildcard test/**/*.cpp) \
 		   $(filter-out src/main.cpp,$(SRC))

TEST_OBJECTS = $(TEST_SRC:%.cpp=$(OBJ_DIR)/%.o)
TEST_TARGET = $(TARGET)_test

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -MMD -o $@

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

test: CFLAGS += -DTEST
test: INCLUDE += -Itest/include/
test: build $(APP_DIR)/$(TEST_TARGET)
	@./$(APP_DIR)/$(TEST_TARGET)

$(APP_DIR)/$(TEST_TARGET): $(TEST_OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $(APP_DIR)/$(TEST_TARGET) $^ $(LDFLAGS)

debug: CFLAGS += -DDEBUG -g
debug: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*

info:
	@echo "Object dir:   ${OBJ_DIR}"
	@echo "Artifact dir: ${APP_DIR}"
	@echo "Sources:      ${SRC}    "
	@echo "Objects:      ${OBJECTS}"

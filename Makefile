.PHONY: all build clean debug info test

CC      = gcc
CFLAGS  = -std=c++17 -Wall -Werror
LDFLAGS = -Llib -lstdc++ -lsqlite3 -lpthread -ldl
INCLUDE = -Iinclude/

BUILD   = ./build
OBJ_DIR = $(BUILD)/objects
APP_DIR = $(BUILD)/apps
SRC     = $(wildcard src/*.cpp) \
		  $(wildcard src/crypto/*.cpp) \
		  $(wildcard src/data/*.cpp) \
		  $(wildcard src/network/*.cpp) \
		  $(wildcard src/storage/*.cpp) \
		  $(wildcard src/random/*.cpp)

OBJECTS = $(SRC:%.cpp=$(OBJ_DIR)/%.o)
TARGET  = aletheia

TEST_DIR = ./test
TEST_OBJ_DIR = $(OBJ_DIR)/test
TEST_SRC = $(wildcard test/*.cpp) \
		   $(wildcard test/http/*.cpp) \
		   $(wildcard test/random/*.cpp) \
		   $(wildcard src/crypto/*.cpp) \
 		   $(wildcard src/data/*.cpp) \
 		   $(wildcard src/network/*.cpp) \
 		   $(wildcard src/storage/*.cpp) \
 		   $(wildcard src/random/*.cpp)

TEST_OBJECTS = $(TEST_SRC:%.cpp=$(TEST_OBJ_DIR)/%.o)
TEST_TARGET = aletheia_test

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

$(TEST_OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -MMD -o $@

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

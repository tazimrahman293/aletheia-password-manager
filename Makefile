.PHONY: all build clean debug info test

CC      = gcc
CFLAGS  = -std=c++17 -Wall -Werror
LDFLAGS = -Llib -lstdc++ -lsqlite3 -lpthread -ldl
INCLUDE = -Iinclude/

BUILD   = ./build
OBJ_DIR = $(BUILD)/objects
APP_DIR = $(BUILD)/apps
SRC     = $(wildcard src/storage/*.cpp) \
		  $(wildcard src/crypto/*.cpp) \
		  $(wildcard src/*.cpp) \
		  
OBJECTS = $(SRC:%.cpp=$(OBJ_DIR)/%.o)
TARGET  = tbd

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

test: all
	@./$(APP_DIR)/$(TARGET)

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


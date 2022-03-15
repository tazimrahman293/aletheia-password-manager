.PHONY: all build clean debug info run test

CC      = gcc
CFLAGS  = -std=c++17 -Wall -Wextra

ifeq ($(OS),Windows_NT)
	LDFLAGS = -Llib/win32
	TARGET_SUFFIX = -win
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		LDFLAGS = -Llib/linux
		TARGET_SUFFIX = -linux
	else
		LDFLAGS = -Llib/darwin
		TARGET_SUFFIX = -osx
	endif
endif
LDFLAGS += -lstdc++ -lsqlite3 -lpthread -ldl -lm
INCLUDE = -Iinclude/

BUILD   = ./build
OBJ_DIR = $(BUILD)/objects
APP_DIR = $(BUILD)/apps
SRC     = $(wildcard src/*.cpp) \
		  $(wildcard src/**/*.cpp)

OBJECTS = $(SRC:%.cpp=$(OBJ_DIR)/%.o)
TARGET  = aletheia$(TARGET_SUFFIX)

TEST_SRC = $(wildcard test/*.cpp) \
		   $(wildcard test/**/*.cpp) \
 		   $(filter-out src/main.cpp,$(SRC))

TEST_OBJECTS = $(TEST_SRC:%.cpp=$(OBJ_DIR)/%.o)
TEST_TARGET = $(TARGET)_test

# Defined at runtime in command-line
ARGS=

all: build $(APP_DIR)/$(TARGET)

run: all
run:
	@./$(APP_DIR)/$(TARGET) $(ARGS)

server-run: all
server-run: ARGS += -S
server-run: run

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
	@./$(APP_DIR)/$(TEST_TARGET) -ltc

$(APP_DIR)/$(TEST_TARGET): $(TEST_OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $(APP_DIR)/$(TEST_TARGET) $^ $(LDFLAGS)

debug: CFLAGS += -DDEBUG -g
debug: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*

print-target:
	@echo "${APP_DIR}/${TARGET}"

print-objs:
	@echo "${OBJECTS}"

info:
	@echo "Object dir:   ${OBJ_DIR}"
	@echo "Artifact dir: ${APP_DIR}"
	@echo "Sources:      ${SRC}    "
	@echo "Objects:      ${OBJECTS}"

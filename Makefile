.PHONY: all \
		build \
		clean \
	    coverage \
	    debug \
	    info \
	    print-coverage \
	    print-objs \
	    print-target \
	    run \
	    server-run \
	    test

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

PROJ_DIR = $(shell pwd)
BUILD   = ./build
OBJ_DIR = $(BUILD)/objects
APP_DIR = $(BUILD)/apps
SRC     = $(wildcard src/*.cpp) \
		  $(wildcard src/**/*.cpp)

HDR     = $(wildcard include/**/*.h) \
		  include/Crypto.h \
		  include/Storage.h

OBJECTS = $(SRC:%.cpp=$(OBJ_DIR)/%.o)
TARGET  = aletheia$(TARGET_SUFFIX)

TEST_SRC = $(wildcard test/*.cpp) \
		   $(wildcard test/**/*.cpp) \
 		   $(filter-out src/main.cpp,$(SRC))

TEST_OBJECTS = $(TEST_SRC:%.cpp=$(OBJ_DIR)/%.o)
TEST_TARGET = $(TARGET)_test

COV_PREF = $(PROJ_DIR)
COV_DIR  = $(BUILD)/coverage
COV_INFO = $(COV_DIR)/coverage.info
COV_HTML = $(COV_DIR)/html
COV_EXCL = '/usr*' \
		   '${PROJ_DIR}/include/httplib.h' \
		   '${PROJ_DIR}/include/json.h' \
		   '${PROJ_DIR}/include/sqlite_orm.h' \
		   '${PROJ_DIR}/test/include/doctest.h'

# Defined at runtime in command-line
ARGS=

all: build $(APP_DIR)/$(TARGET)

coverage: CFLAGS += --coverage
coverage: build all test $(OBJECTS) $(TEST_OBJECTS)
	@./$(APP_DIR)/$(TEST_TARGET) $(ARGS)
	@export GCOV_PREFIX=$(PROJ_DIR) && echo $$GCOV_PREFIX && gcov $(OBJECTS)
	ls .
	ls -R $(OBJ_DIR)
	ls $(COV_DIR)
	@lcov -c -d . -o $(COV_INFO)
	@lcov -r $(COV_INFO) $(COV_EXCL) -o $(COV_INFO)
	@genhtml $(COV_INFO) -o $(COV_HTML)
	@mv -f *.gcov $(COV_DIR)

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
	@mkdir -p $(COV_DIR)

test: CFLAGS += -DTEST
test: INCLUDE += -Itest/include/
test: build $(APP_DIR)/$(TEST_TARGET)
	@./$(APP_DIR)/$(TEST_TARGET) -ltc

$(APP_DIR)/$(TEST_TARGET): $(TEST_OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $(APP_DIR)/$(TEST_TARGET) $^ $(LDFLAGS)

debug: CFLAGS += -DDEBUG -g
debug: all

print-coverage:
	@lcov --list $(COV_INFO)

print-target:
	@echo "${APP_DIR}/${TARGET}"

print-objs:
	@echo "${OBJECTS}"

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
	-@rm -rvf $(COV_DIR)/*

info:
	@echo "Object dir:   ${OBJ_DIR}"
	@echo "Artifact dir: ${APP_DIR}"
	@echo "Sources:      ${SRC}    "
	@echo "Objects:      ${OBJECTS}"

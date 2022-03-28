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

# Get the OS of the current system and set the target flags appropriately
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
LDFLAGS += -lstdc++ -lsqlite3 -lpthread -ldl -lm -L./lib -lhydrogen
INCLUDE = -Iinclude/

PROJ_DIR = $(shell pwd)
BUILD   = ./build
OBJ_DIR = $(BUILD)/objects
APP_DIR = $(BUILD)/apps
SRC     = $(wildcard src/*.cpp) \
		  $(wildcard src/**/*.cpp)

HDR     = $(wildcard include/**/*.h) \
		  include/Storage.h

OBJECTS = $(SRC:%.cpp=$(OBJ_DIR)/%.o)
TARGET  = aletheia$(TARGET_SUFFIX)

TEST_SRC = $(wildcard test/*.cpp) \
		   $(wildcard test/**/*.cpp) \
 		   $(filter-out src/main.cpp,$(SRC))

TEST_OBJECTS = $(TEST_SRC:%.cpp=$(OBJ_DIR)/%.o)
TEST_TARGET = $(TARGET)_test

# Coverage prefix (for gcov)
COV_PREF = $(PROJ_DIR)
# Coverage build folder
COV_DIR  = $(BUILD)/coverage
# Location of main lcov .info file
COV_INFO = $(COV_DIR)/coverage.info
# Output directory for genhtml report files
COV_HTML = $(COV_DIR)/html
# List of exclusions from the lcov report
COV_EXCL = '/usr*' \
		   '${PROJ_DIR}/include/httplib.h' \
		   '${PROJ_DIR}/include/json.h' \
		   '${PROJ_DIR}/include/sqlite_orm.h' \
		   '${PROJ_DIR}/test/*'

TEST_RESULT  = $(COV_DIR)/test_results.xml
TEST_FLAGS   =

# Defined at runtime in command-line
ARGS=

# Do a full build of the main app target
all: build $(APP_DIR)/$(TARGET)

# Run code coverage analysis by using gcov on a modified version of the test target
# Generate a report using lcov/genhtml
coverage: CFLAGS += --coverage
coverage: build all auto-test $(OBJECTS) $(TEST_OBJECTS)
	@./$(APP_DIR)/$(TEST_TARGET) $(ARGS)
	@export GCOV_PREFIX=$(PROJ_DIR) && echo $$GCOV_PREFIX && gcov $(OBJECTS)
	@lcov -c -d . -o $(COV_INFO)
	@lcov -r $(COV_INFO) $(COV_EXCL) -o $(COV_INFO)
	@genhtml $(COV_INFO) -o $(COV_HTML)
	@mv -f *.gcov $(COV_DIR)

# Perform a full build and run the resulting binary with ARGS
run: all
run:
	@./$(APP_DIR)/$(TARGET) $(ARGS)

# Perform a full build and run the resulting binary with ARGS and -S for server mode
server-run: all
server-run: ARGS += -S
server-run: run

# Builds all object files from source files without linking
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -MMD -o $@

# Links object files and external libs into the main target binary
$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)

# Prepares build directories
build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(COV_DIR)

# Performs a full build and run of the test target binary and outputs a test report
# Report format is JUnit XML
test: CFLAGS += -DTEST
test: INCLUDE += -Itest/include/
test: build $(APP_DIR)/$(TEST_TARGET)
	@./$(APP_DIR)/$(TEST_TARGET) $(TEST_FLAGS)

auto-test: TEST_FLAGS += -r=junit -o=$(TEST_RESULT)
auto-test: test

# Links object files and external libs into the test target binary
$(APP_DIR)/$(TEST_TARGET): $(TEST_OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $(APP_DIR)/$(TEST_TARGET) $^ $(LDFLAGS)

# Runs a full build with gdb flags enabled
debug: CFLAGS += -DDEBUG -g -fno-inline -O0
debug: all

# Prints a coverage report summary to stdout
print-coverage:
	@lcov --list $(COV_INFO)

# Prints the name of the main target to stdout
print-target:
	@echo "${APP_DIR}/${TARGET}"

# Prints a list of all intermediate object files to stdout
print-objs:
	@echo "${OBJECTS}"

# Removes all files from the build directories
clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
	-@rm -rvf $(COV_DIR)/*

# Performs a normal clean and deletes ALL .sqlite3 files in the current folder
superclean: clean
superclean:
	-@rm -vf *.sqlite3

# Provides info on important directories and files for this project
info:
	@echo "Object dir:   ${OBJ_DIR}"
	@echo "Artifact dir: ${APP_DIR}"
	@echo "Sources:      ${SRC}    "
	@echo "Objects:      ${OBJECTS}"

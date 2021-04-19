SRC_DIR		= ./src
TEST_DIR	= ./test
OBJ_DIR   = ./build
EXEC_OBJ_FILE  := $(OBJ_DIR)/ppmc.o
SRC_FILES 		 := $(wildcard $(SRC_DIR)/*.cpp)
TEST_FILES 		 := $(wildcard $(TEST_DIR)/*.cpp)
OBJ_FILES 		 := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
OBJ_FILES_NOPP := $(filter-out $(EXEC_OBJ_FILE), $(OBJ_FILES))
TEST_OBJ_FILES := $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/test/%.o,$(TEST_FILES))
CC       := clang++-10
CPPFLAGS := -std=c++17 -Wall -O3 -MMD
LDFLAGS  := 

.PHONY: directories

all: directories ppmc ppmc_test

clean:
	rm -rf ${OBJ_DIR}

ppmc: $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

ppmc_test: $(OBJ_FILES_NOPP) $(TEST_OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) -c -o $@ $<

$(OBJ_DIR)/test/%.o: $(OBJ_FILES) $(TEST_FILES)
	$(CC) $(CPPFLAGS) -c -o $@ $^

directories: ${OBJ_DIR}

${OBJ_DIR}:
	mkdir -p  ${OBJ_DIR}
	mkdir -p  ${OBJ_DIR}/test

-include $(OBJ_FILES:.o=.d)

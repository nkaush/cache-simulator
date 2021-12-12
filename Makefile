GTEST_DIR := gtest-1.8.0
GTEST_LIB := $(GTEST_DIR)/make/gtest_main.a

CXX = clang++
CPPFLAGS = -isystem $(GTEST_DIR)/include
CXXFLAGS = -g -Wall -Werror -Wno-unused-parameter -Wno-unused-private-field -std=c++11 -c
LD = $(CXX)
LDFLAGS = 

EXE = cachesim

OBJS_DIR = .objs
OBJS = src/cache.o src/cache.o src/cacheblock.o src/cacheconfig.o src/cachesimulator.o src/utils.o apps/main.o 

.PHONY: all clean

all: cachesim unit_tests

$(EXE): $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS)) 
	$(LD) $^ $(LDFLAGS) -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/tests
	@mkdir -p $(OBJS_DIR)/src
	@mkdir -p $(OBJS_DIR)/apps

# cachesim: cache.o cacheblock.o cacheconfig.o cachesimulator.o main.o utils.o
# 	$(LD) $(LDFLAGS) -o $@ $(filter %.o,$^)

$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

unit_tests: cacheblock.o cacheblock_test.o cacheconfig.o cacheconfig_test.o \
            utils.o utils_test.o $(GTEST_LIB)
	$(LD) $(LDFLAGS) -pthread -o $@ $^

clean:
	rm -rf $(OBJS_DIR) *.exe simplecache cachesim unit_tests *.dSYM

# Google Test setup

$(GTEST_LIB):
	$(MAKE) -C $(dir $(GTEST_LIB)) CXX=$(CXX) gtest_main.a

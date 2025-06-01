CXX = g++
CXXFLAGS = -std=c++11 -Iinclude -Wall -Wextra

SRC = src/Matrix.cpp src/Vector.cpp src/LinearSystem.cpp
TESTS = tests/test_linearsystem.cpp
CPU_REGRESSION = cpu_regression.cpp

all: test_linearsystem cpu_regression

test_linearsystem: $(SRC) $(TESTS)
	$(CXX) $(CXXFLAGS) $(SRC) $(TESTS) -o test_linearsystem

cpu_regression: $(SRC) $(CPU_REGRESSION)
	$(CXX) $(CXXFLAGS) $(SRC) $(CPU_REGRESSION) -o cpu_regression

run_test: test_linearsystem
	./test_linearsystem

run_cpu: cpu_regression
	./cpu_regression

clean:
ifeq ($(OS),Windows_NT)
	del /Q test_linearsystem.exe cpu_regression.exe 2>nul
else
	rm -f test_linearsystem cpu_regression
endif

.PHONY: all clean run_test run_cpu

CXX = g++
CXXFLAGS = -Wall -std=c++17 --coverage
LDFLAGS = --coverage

OBJS = main.o utils.o  # все объектные файлы
TARGET = my_program

$(TARGET): $(OBJS)
    $(CXX) $(LDFLAGS) -o $@ $(OBJS)

%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

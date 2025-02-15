CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

TARGET = app

SRC = main.cpp GA.cpp Travel.cpp

OBJ = $(SRC:.cpp=.o)

DEPS = GA.hpp Travel.hpp

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

rebuild: clean $(TARGET)
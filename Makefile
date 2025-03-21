CXX = clang++
CXXFLAGS = -Wall -Wextra -O2 -std=c++20

SRCS = main.cc Board-impl.cc PieceManager-impl.cc Player-impl.cc
OBJS = $(SRCS:.cc=.o)
DEPS = Board.h Piece.h PieceManager.h Player.h Building.h

TARGET = watopoly

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cc $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

XX = g++
CPPFLAGS = -g -Wall -std=c++0x

src = $(wildcard *.cpp)
target = $(patsubst %.cpp, %, ${src})

.PHONY: all clean

all: $(target)

clean:
	rm -f $(target)

# Makefile for CS350
# Shang-Chun, Lin 2020

CPP = g++
CPPFLAGS = -Wall -Werror -g
SRC = list.cpp main.cpp
OUT = Shanglin_Project

$(OUT): $(SRC)
	$(CPP) $(CPPFLAGS) -o $(OUT) $(SRC) -lncurses

clean:
	-rm -f $(OUT) $(OUT).zip

zip:
	zip -v $(OUT).zip *.cpp *.md Makefile *.h *.txt

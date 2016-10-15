LINE_CPP_O=g++ -c -Wall -o $@ $(CPPFLAG) $^
obj/%.o: src/%.cpp %
	$(LINE_CPP_O)
obj/%.o: src/%.cpp
	$(LINE_CPP_O)

PROGRAM=KastiBob_run
CPPFLAG= --std=c++11

all: $(PROGRAM)

obj/main.o: src/main.cpp

$(PROGRAM): obj/main.o
	g++ $^ -o $@

test: all
	./$(PROGRAM) Kasti.exe

clean:
	@(rm obj/*.o || true)
	@(rm $(PROGRAM) || true)

LINE_CPP_O=$(CXX) -c -Wall -o $@ $(CPPFLAG) $<
obj/%.o: src/%.cpp %
	$(LINE_CPP_O)
obj/%.o: src/%.cpp
	$(LINE_CPP_O)
PROGRAM=KastiBob_logic
CPPFLAG= --std=c++11 -lws2_32 -lgmp

all: obj $(PROGRAM)
obj:
	mkdir -p obj
obj/main.o: src/main.cpp
$(PROGRAM): obj/main.o
	$(CXX) $^ -o $@ $(CPPFLAG)

test: all
	./$(PROGRAM)

clean:
	@(rm obj/* || true)
	@(rm $(PROGRAM) || true)

LINE_CPP_O=$(CXX) -c -Wall -o $@ $(CPPFLAG) $<
obj/%.o: src/%.cpp %
	$(LINE_CPP_O)
obj/%.o: src/%.cpp
	$(LINE_CPP_O)
PROGRAM=KastiBob_run
CPPFLAG= --std=c++11

all: obj $(PROGRAM)
obj:
	mkdir -p obj
obj/objectfile.o: src/objectfile.cpp src/objectfile.hpp
obj/main.o: src/main.cpp src/objectfile.hpp

obj/remoteCode.o: src/remoteCode.c
	$(GCC32) -o $@ -c $^

obj/remoteCode.h.gen: obj/remoteCode.o
	../bin2c/bin2c $< > $@

obj/remoteCode_string.o: src/remoteCode_string.cpp obj/remoteCode.h.gen


$(PROGRAM): obj/main.o obj/remoteCode_string.o obj/objectfile.o
	$(CXX) $^ -o $@

test: all
	./$(PROGRAM) Kasti.exe

clean:
	@(rm obj/* || true)
	@(rm $(PROGRAM) || true)

LINE_CPP_O=g++ -c -Wall -o $@ $(CPPFLAG) $<
obj/%.o: src/%.cpp %
	$(LINE_CPP_O)
obj/%.o: src/%.cpp
	$(LINE_CPP_O)

PROGRAM=KastiBob_run
CPPFLAG= --std=c++11

all: $(PROGRAM)


obj/objectfile.o: src/objectfile.cpp src/objectfile.hpp
obj/main.o: src/main.cpp src/objectfile.hpp

obj/remoteCode.bin.gen: src/remoteCode.c
	gcc -m32 -o $@ -c $^

obj/remoteCode.h.gen: obj/remoteCode.bin.gen
	../bin2c/bin2c $< > $@

obj/remoteCode_string.o: src/remoteCode_string.cpp obj/remoteCode.h.gen


$(PROGRAM): obj/main.o obj/remoteCode_string.o obj/objectfile.o
	g++ $^ -o $@

test: all
	./$(PROGRAM) Kasti.exe

clean:
	@(rm obj/* || true)
	@(rm $(PROGRAM) || true)

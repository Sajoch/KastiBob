LINE_CPP_O=$(CXX32) -c -Wall -o $@ $(CPPFLAG) $<
obj/%.o: src/%.cpp %
	$(LINE_CPP_O)
obj/%.o: src/%.cpp
	$(LINE_CPP_O)

PROGRAM=Kasti_re.dll
CPPFLAG= --std=c++11 -DBUILDING_DLL -static-libgcc -static-libstdc++

all: obj $(PROGRAM)
obj:
	mkdir -p obj

obj/main.o: src/main.cpp src/console.hpp
obj/console.o: src/console.cpp src/console.hpp

$(PROGRAM): obj/main.o obj/console.o
	$(CXX32) -shared $^ -o $@ $(CPPFLAG)

test: all
	(cp $(PROGRAM) ../kclient_v1/. || true)
	../running_inject/KastiBob_run.exe Kasti.exe

clean:
	@(rm obj/* || true)
	@(rm $(PROGRAM) || true)

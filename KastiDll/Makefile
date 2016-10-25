LINE_CPP_O=$(CXX) -c -Wall -o $@ $(CPPFLAG) $<
obj/%.o: src/%.cpp %
	$(LINE_CPP_O)
obj/%.o: src/%.cpp
	$(LINE_CPP_O)

CXX=i686-w64-mingw32-g++

PROGRAM=Kasti_re.dll
CPPFLAG= --std=c++11 -DBUILDING_DLL

all: $(PROGRAM)

obj/main.o: src/main.cpp

$(PROGRAM): obj/main.o
	$(CXX) -shared $^ -o $@

test: all
	cp $(PROGRAM) ../kclient_v1/.
	../running_inject/KastiBob_run.exe Kasti.exe

clean:
	@(rm obj/* || true)
	@(rm $(PROGRAM) || true)

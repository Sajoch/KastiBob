CXX=$(PRE)g++
RCC=$(PRE)rcc
UIC=$(PRE)uic

INCLUDEPATH=inc
CXXFLAGS=--std=c++14
LIBS=
PROGRAM=KastiBob

CXXFLAGS+= $(patsubst %,-l%,$(LIBS))
CXXFLAGS+= $(patsubst %,-I%,$(INCLUDEPATH))
CXXFLAGS+= $(patsubst %,-L%,$(LIBPATH))
CXX+=$(CXXFLAGS)

cpp_files=$(wildcard src/*.cpp)
cpp_objects=$(patsubst src/%,obj/%.o,$(cpp_files))
OBJS=$(cpp_objects)

all: $(PROGRAM)
list-tools:
	@echo "CXX = "$(CXX)
	@echo "RCC = "$(RCC)
	@echo "UIC = "$(UIC)

build/src/%.cpp: src/%.cpp
	$(CXX) -MM $^
	#@echo "dep" $@

obj/%.cpp.o: build/src/%.cpp
	@echo "compile" $@

$(PROGRAM): $(OBJS)
	@echo "objects" $<
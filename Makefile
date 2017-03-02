CXX=$(PRE)g++
RCC=$(PRE)rcc
UIC=$(PRE)uic

INCLUDEPATH=inc
CXXFLAGS=--std=c++14
LIBS=
PROGRAM=build/KastiBob

CXXFLAGS+= $(patsubst %,-I%,$(INCLUDEPATH))
CXX+=$(CXXFLAGS)
CXXFLAGS+= $(patsubst %,-l%,$(LIBS))
CXXFLAGS+= $(patsubst %,-L%,$(LIBPATH))

cpp_files=$(wildcard src/*.cpp)
cpp_objects=$(patsubst src/%,build/obj/%.o,$(cpp_files))
cpp_deps=$(patsubst src/%,build/deps/%.d,$(cpp_files))
OBJS=$(cpp_objects)

test: run_$(PROGRAM)
debug: debug_$(PROGRAM)
all: make_deps_cpp $(PROGRAM)
list-tools:
	@echo "CXX = "$(CXX)
	@echo "RCC = "$(RCC)
	@echo "UIC = "$(UIC)

build:
	mkdir -p build

deps: build obj
	mkdir -p build/deps
obj: build
	mkdir -p build/obj

make_deps_cpp: $(cpp_deps)

build/deps/%.cpp.d: src/%.cpp
	@echo "Make deps "$@
	$(CXX) -MM -MT build/obj/$*.cpp.o $< -o $@

build/obj/%.cpp.o:
	@echo "Complie "$@
	$(CXX) -c $< -o $@

-include build/deps/*.d
$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@
run_$(PROGRAM): all
	./$(PROGRAM)
debug_$(PROGRAM): all
	gdb $(PROGRAM)
	
.PHONY: clean clean_program clean_obj_cpp clean_deps_cpp
clean_program:
	@(rm $(PROGRAM) >/dev/null 2>&1 || true)
clean_obj_cpp:
	@(rm -rf build/obj/* >/dev/null 2>&1 || true)
clean_deps_cpp:
	@(rm -rf build/deps/* >/dev/null 2>&1 || true)
clean: clean_deps_cpp clean_obj_cpp clean_program
	@echo "ok"

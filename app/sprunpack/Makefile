obj/%.o :
	@echo "-Compile" $@
	@$(CXX) -c -Wall -o $@ $(CPPFLAG) $<
PROGRAM=sprunpack
CPPFLAG= --std=c++11 -ggdb

dll: obj $(PROGRAM).dll
all: obj $(PROGRAM)
obj:
	mkdir -p obj

OBJS=main file
OBJECTS=$(patsubst %,obj/%.o,$(OBJS))

obj/main.o: src/main.cpp src/file.hpp
obj/file.o: src/file.cpp src/file.hpp

$(PROGRAM): $(OBJECTS)
	@echo "============ Compile" $@ "=============="
	@$(CXX) $^ -o $@ $(CPPFLAG)

test: all
	./$(PROGRAM) ../../kclient_v1/Kasti.spr

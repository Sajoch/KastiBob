obj/%.o :
	@echo "-Compile" $@
	@$(CXX) -c -Wall -o $@ $(CPPFLAG) $<
PROGRAM=KastiBob_logic
CPPFLAG= --std=c++11 -fdiagnostics-color -lws2_32 -lgmp

all: obj $(PROGRAM)
obj:
	mkdir -p obj

OBJS=main cipher packet LoginPacket network
OBJECTS=$(patsubst %,obj/%.o,$(OBJS))
obj/packet.o: src/packet.cpp src/packet.hpp
obj/cipher.o: src/cipher.cpp src/cipher.hpp
obj/network.o: src/network.cpp src/network.hpp
obj/LoginPacket.o: src/packets/LoginPacket.cpp src/packets/LoginPacket.hpp
obj/main.o: src/main.cpp
$(PROGRAM): $(OBJECTS)
	@echo "============ Compile" $@ "=============="
	@$(CXX) $^ -o $@ $(CPPFLAG)

test: all
	./$(PROGRAM)

clean:
	@(rm obj/* || true)
	@(rm $(PROGRAM) || true)

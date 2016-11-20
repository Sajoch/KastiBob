obj/%.o :
	@echo "-Compile" $@
	@$(CXX) -c -Wall -o $@ $(CPPFLAG) $<
PROGRAM=KastiBob_logic
CPPFLAG= --std=c++11 -lws2_32 -lgmp -lpocoNet -lpocoFoundation

all: obj $(PROGRAM)
obj:
	mkdir -p obj
PACKETS=LoginPacket
OBJS=main cipher packet $(PACKETS) network client
OBJECTS=$(patsubst %,obj/%.o,$(OBJS))
obj/client.o: src/client.cpp src/client.hpp src/packets/LoginPacket.hpp
obj/packet.o: src/packet.cpp src/packet.hpp
obj/cipher.o: src/cipher.cpp src/cipher.hpp
obj/network.o: src/network.cpp src/network.hpp
obj/LoginPacket.o: src/packets/LoginPacket.cpp src/packets/LoginPacket.hpp
obj/main.o: src/main.cpp src/client.hpp
$(PROGRAM): $(OBJECTS)
	@echo "============ Compile" $@ "=============="
	@$(CXX) $^ -o $@ $(CPPFLAG)

test: all
	./$(PROGRAM)

clean:
	@(rm obj/* || true)
	@(rm $(PROGRAM) || true)

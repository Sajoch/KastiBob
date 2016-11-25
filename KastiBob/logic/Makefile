obj/%.o :
	@echo "-Compile" $@
	@$(CXX) -c -Wall -o $@ $(CPPFLAG) $<
PROGRAM=KastiBob_logic
CPPFLAG= --std=c++11 -ggdb -lgmp -lpocoNet -lpocoFoundation

all: obj $(PROGRAM)
obj:
	mkdir -p obj
PACKETS=Login Ping
OBJS=main cipher packet network client

OBJS+=$(patsubst %,%Packet,$(PACKETS))
OBJECTS=$(patsubst %,obj/%.o,$(OBJS))
obj/client.o: src/client.cpp src/client.hpp src/packets/LoginPacket.hpp src/packets/PingPacket.hpp
obj/packet.o: src/packet.cpp src/packet.hpp
obj/cipher.o: src/cipher.cpp src/cipher.hpp
obj/network.o: src/network.cpp src/network.hpp
obj/LoginPacket.o: src/packets/LoginPacket.cpp src/packets/LoginPacket.hpp
obj/PingPacket.o: src/packets/PingPacket.cpp src/packets/PingPacket.hpp
obj/main.o: src/main.cpp src/client.hpp
$(PROGRAM): $(OBJECTS)
	@echo "============ Compile" $@ "=============="
	@$(CXX) $^ -o $@ $(CPPFLAG)

debug: all
	gdb $(PROGRAM)

test: all
	./$(PROGRAM)

clean:
	@(rm obj/* || true)
	@(rm $(PROGRAM) || true)

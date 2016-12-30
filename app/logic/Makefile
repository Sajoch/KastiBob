obj/%.o :
	@echo "-Compile" $@
	@$(CXX) -c -Wall -o $@ $(CPPFLAG) $<
PROGRAM=KastiBob_logic
CPPFLAG= --std=c++11 -ggdb -lgmp -lPocoNet -lPocoFoundation -DDLL

dll: obj $(PROGRAM).dll
all: obj $(PROGRAM)
obj:
	mkdir -p obj
PACKETS=Login Ping Move
OBJS=main cipher packet network client ground square \
		 utils outfit

OBJS+=$(patsubst %,%Packet,$(PACKETS))
OBJECTS=$(patsubst %,obj/%.o,$(OBJS))
PACKETHEADERS=$(patsubst %,src/packets/%Packet.hpp,$(PACKETS))
obj/client.o: src/client.cpp src/client.hpp $(PACKETHEADERS)
obj/packet.o: src/packet.cpp src/packet.hpp
obj/cipher.o: src/cipher.cpp src/cipher.hpp
obj/network.o: src/network.cpp src/network.hpp
obj/ground.o: src/ground.cpp src/ground.hpp src/utils.hpp src/square.hpp
obj/square.o: src/square.cpp src/square.hpp src/utils.hpp src/creature.hpp
obj/utils.o: src/utils.cpp src/utils.hpp
obj/outfit.o: src/outfit.cpp src/outfit.hpp
obj/LoginPacket.o: src/packets/LoginPacket.cpp src/packets/LoginPacket.hpp
obj/PingPacket.o: src/packets/PingPacket.cpp src/packets/PingPacket.hpp
obj/MovePacket.o: src/packets/MovePacket.cpp src/packets/MovePacket.hpp
obj/main.o: src/main.cpp src/client.hpp
$(PROGRAM): $(OBJECTS)
	@echo "============ Compile" $@ "=============="
	@$(CXX) $^ -o $@ $(CPPFLAG)
$(PROGRAM).dll: $(OBJECTS)
	@echo "============ Compile" $@ "=============="
	@$(CXX) $^ -shared -o $@ $(CPPFLAG)
$(PROGRAM).so: $(OBJECTS)
	@echo "============ Compile" $@ "=============="
	@$(CXX) $^ -shared -o $@ $(CPPFLAG)
debug: all
	gdb $(PROGRAM)

test: all
	./$(PROGRAM)

clean:
	@(rm obj/* || true)
	@(rm $(PROGRAM) $(PROGRAM).so $(PROGRAM).dll || true)

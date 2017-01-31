obj/%.o :
	@echo "-Compile" $@
	@$(CXX) -c -o $@ $(CPPFLAG) $<

src/%.hpp.gch : 
	@echo "precompile" $@
	@$(CXX) -o $@ $<

PROGRAM=KastiBob_logic
CPPFLAG= --std=c++11 -Wall -ggdb -lgmp -lPocoNet -lPocoFoundation -DDLL 
ifeq ($(OS),LINUX)
CPPFLAG+= -fPIC
endif

dll: obj obj_ext_c $(PROGRAM).dll
so: obj obj_ext_c lib$(PROGRAM).so
all: obj obj_ext_c $(PROGRAM)
obj:
	mkdir -p obj
obj_ext_c:
	mkdir -p obj_ext_c
PACKETS=Login Ping Move OneByte
OBJS=main cipher packet network client ground square \
		 utils outfit creature extendClient item datLoader
extendClient_CPP=$(wildcard src/extendClient/*.cpp)
extendClient_OBJ=$(patsubst src/extendClient/%.cpp,obj_ext_c/%.o,$(extendClient_CPP))
OBJS+=$(patsubst %,%Packet,$(PACKETS))
OBJECTS=$(extendClient_OBJ) $(patsubst %,obj/%.o,$(OBJS))
PACKETHEADERS=$(patsubst %,src/packets/%Packet.hpp,$(PACKETS))
obj_ext_c/%.o: src/extendClient/%.cpp $(PACKETHEADERS) 
	@echo "-Compile" $@
	@$(CXX) -c -o $@ $(CPPFLAG) $<
obj/client.o: src/client.cpp src/client.hpp $(PACKETHEADERS) src/extendClient.hpp
obj/packet.o: src/packet.cpp src/packet.hpp
obj/cipher.o: src/cipher.cpp src/cipher.hpp
obj/network.o: src/network.cpp src/network.hpp
obj/ground.o: src/ground.cpp src/ground.hpp src/utils.hpp src/square.hpp
obj/square.o: src/square.cpp src/square.hpp src/utils.hpp src/creature.hpp
obj/creature.o: src/creature.cpp src/creature.hpp
obj/extendClient.o: src/extendClient.cpp src/extendClient.hpp
obj/datLoader.o: src/datLoader.cpp src/datLoader.hpp
obj/utils.o: src/utils.cpp src/utils.hpp
obj/outfit.o: src/outfit.cpp src/outfit.hpp
obj/item.o: src/item.cpp src/item.hpp
obj/LoginPacket.o: src/packets/LoginPacket.cpp src/packets/LoginPacket.hpp
obj/PingPacket.o: src/packets/PingPacket.cpp src/packets/PingPacket.hpp
obj/MovePacket.o: src/packets/MovePacket.cpp src/packets/MovePacket.hpp
obj/OneBytePacket.o: src/packets/OneBytePacket.cpp src/packets/OneBytePacket.hpp
obj/main.o: src/main.cpp src/client.hpp
$(PROGRAM): $(OBJECTS)
	@echo "============ Compile" $@ "=============="
	@$(CXX) $^ -o $@ $(CPPFLAG)
$(PROGRAM).dll: $(OBJECTS)
	@echo "============ Compile" $@ "=============="
	@$(CXX) $^ -shared -o $@ $(CPPFLAG)
lib$(PROGRAM).so: $(OBJECTS)
	@echo "============ Compile" $@ "=============="
	@$(CXX) $^ -shared -o $@ $(CPPFLAG)
debug: all
	gdb $(PROGRAM)

test: all
	./$(PROGRAM)

clean:
	@(rm obj/* || true)
	@(rm obj_ext_c/* || true)
	@(rm $(PROGRAM) $(PROGRAM).so $(PROGRAM).dll || true)

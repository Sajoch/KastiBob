CPPFLAG= --std=c++11 -lQt5Widgets -lQt5WebKit -lQt5Core -lQt5WebKitWidgets \
-lQt5Gui \
-L../logic -lKastiBob_logic -I../logic/src -Iinclude -Iuis_h
obj/%.o :
	@echo "-Compile" $@
	@$(CXX) -c -Wall -o $@ $(CPPFLAG) $<

PROGRAM=KastiBobGui
LOGIC=KastiBob_logic.dll

obj:
	mkdir -p obj
uis_h:
	mkdir -p uis_h
moc_cpp:
	mkdir -p moc_cpp

all: obj uis_h moc_cpp $(PROGRAM)
RSC=index.html style.css main.js render.js jquery-3.1.1.min.js \
		jquery-ui.min.js communication.js console.js img.js keys.js \
		ui.js
ORSC=$(patsubst %,files/%,$(RSC))

MOC=jsbridge
MOCS=$(patsubst %,moc_%.gen,$(MOC))
obj/resource.gen.cpp: resource.qrc $(ORSC)
	rcc resource.qrc -o $@

OBJS=main charselect loginform gamewindow jsbridge \
		 resource file spriteLoader $(MOCS)
uis_h/%.gen.h :
	@echo "-Compile from ui" $@
	@uic $< -o $@
moc_cpp/%.gen.cpp :
	@echo "-Compile by moc" $@
	@moc $< -o $@
uis_h/charselect.gen.h: uis/charselect.ui
uis_h/loginform.gen.h: uis/loginform.ui
uis_h/gamewindow.gen.h: uis/gamewindow.ui
obj/resource.o: obj/resource.gen.cpp
obj/charselect.o: src/charselect.cpp include/loginform.h include/charselect.h \
	uis_h/charselect.gen.h include/gamewindow.h
obj/loginform.o: src/loginform.cpp include/loginform.h uis_h/loginform.gen.h \
	include/charselect.h
obj/gamewindow.o: src/gamewindow.cpp uis_h/gamewindow.gen.h include/gamewindow.h
obj/jsbridge.o: src/jsbridge.cpp include/jsbridge.h include/gamewindow.h
moc_h/jsbridge.gen.cpp: include/jsbridge.h
obj/moc_jsbridge.gen.o: moc_cpp/jsbridge.gen.cpp
obj/main.o: src/main.cpp include/loginform.h include/charselect.h include/gamewindow.h
obj/file.o: src/file.cpp include/file.hpp
obj/spriteLoader.o: src/spriteLoader.cpp include/spriteLoader.hpp include/file.hpp

#headers
include/gamewindow.h: uis_h/gamewindow.gen.h
include/charselect.h: uis_h/charselect.gen.h
include/loginform.h: uis_h/loginform.gen.h
moc_cpp/jsbridge.gen.cpp: include/jsbridge.h

OBJECTS=$(patsubst %,obj/%.o,$(OBJS))

$(PROGRAM): $(OBJECTS) $(LOGIC)
	@echo "============ Compile" $@ "=============="
	$(CXX) $^ -o $@ $(CPPFLAG)

debug: all
	gdb $(PROGRAM) -q -x gdb_start

test: all
	./$(PROGRAM)
$(LOGIC): ../logic/$(LOGIC)
	cp $^ $@
clean:
	@(rm obj/* || true)
	@(rm $(PROGRAM) || true)

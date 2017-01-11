CPPFLAG= --std=c++11 -lQt5Widgets -lQt5WebKit -lQt5Core -lQt5WebKitWidgets \
-lQt5Gui \
-L../logic -lKastiBob_logic -I../logic
obj/%.o :
	@echo "-Compile" $@
	@$(CXX) -c -Wall -o $@ $(CPPFLAG) $<

PROGRAM=KastiBobGui
LOGIC=KastiBob_logic.dll

obj:
	mkdir -p obj
uis_cpp:
	mkdir -p uis_cpp
moc_h:
	mkdir -p moc_h

all: obj uis_cpp moc_h $(PROGRAM)
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
uis_cpp/%.gen.h :
	@echo "-Compile from ui" $@
	@uic $< -o $@
moc_h/%.gen.cpp :
	@echo "-Compile by moc" $@
	@moc $< -o $@
uis_cpp/charselect.gen.h: uis/charselect.ui
uis_cpp/loginform.gen.h: uis/loginform.ui
uis_cpp/gamewindow.gen.h: uis/gamewindow.ui
obj/resource.o: obj/resource.gen.cpp
obj/charselect.o: charselect.cpp loginform.h charselect.h \
	uis_cpp/charselect.gen.h gamewindow.h
obj/loginform.o: loginform.cpp loginform.h uis_cpp/loginform.gen.h \
	charselect.h
obj/gamewindow.o: gamewindow.cpp uis_cpp/gamewindow.gen.h gamewindow.h
obj/jsbridge.o: jsbridge.cpp jsbridge.h gamewindow.h
moc_h/jsbridge.gen.cpp: jsbridge.h
obj/moc_jsbridge.gen.o: moc_h/jsbridge.gen.cpp
obj/main.o: main.cpp loginform.h charselect.h gamewindow.h
obj/file.o: file.cpp file.hpp
obj/spriteLoader.o: spriteLoader.cpp spriteLoader.hpp file.hpp

#headers
gamewindow.h: uis_cpp/gamewindow.gen.h
charselect.h: uis_cpp/charselect.gen.h
loginform.h: uis_cpp/loginform.gen.h
moc_h/jsbridge.gen.h: jsbridge.h

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

CPPFLAG= --std=c++11 -lQt5Widgets -lQt5WebKit -lQt5Core -lQt5WebKitWidgets
obj/%.o :
	@echo "-Compile" $@
	@$(CXX) -c -Wall -o $@ $(CPPFLAG) $<

PROGRAM=KastiBobGui

obj:
	mkdir -p obj
uis_cpp:
	mkdir -p uis_cpp

all: obj uis_cpp $(PROGRAM)
RSC=index.html style.css main.js render.js jquery-3.1.1.min.js \
		jquery-ui.min.js
ORSC=$(patsubst %,files/%,$(RSC))
obj/resource.gen.cpp: resource.qrc $(ORSC)
	rcc resource.qrc -o $@

OBJS=main charselect loginform gamewindow jsbrige \
		 resource
uis_cpp/%.gen.h :
	@echo "-Compile from ui" $@
	@uic $< -o $@

uis_cpp/charselect.gen.h: uis/charselect.ui
uis_cpp/loginform.gen.h: uis/loginform.ui
uis_cpp/gamewindow.gen.h: uis/gamewindow.ui
obj/resource.o: obj/resource.gen.cpp
obj/charselect.o: charselect.cpp charselect.h
obj/loginform.o: loginform.cpp loginform.h
obj/gamewindow.o: gamewindow.cpp gamewindow.h
obj/jsbrige.o: jsbrige.cpp jsbrige.h
obj/main.o: main.cpp charselect.h loginform.h gamewindow.h

#headers
gamewindow.h: uis_cpp/gamewindow.gen.h
charselect.h: uis_cpp/charselect.gen.h
loginform.h: uis_cpp/loginform.gen.h

OBJECTS=$(patsubst %,obj/%.o,$(OBJS))

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

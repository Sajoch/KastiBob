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
RSC=index.html style.css main.js
ORSC=$(patsubst %,files/%,$(RSC))
obj/resource.cpp: resource.qrc $(ORSC)
	rcc resource.qrc -o $@

OBJS=main charselect loginform gamewindow jsbrige \
		 resource
uis_cpp/%.h :
	@echo "-Compile from ui" $@
	@uic $< -o $@

uis_cpp/charselect.h: uis/charselect.ui
uis_cpp/loginform.h: uis/loginform.ui
uis_cpp/gamewindow.h: uis/gamewindow.ui
obj/resource.o: obj/resource.cpp
obj/charselect.o: charselect.cpp charselect.h uis_cpp/charselect.h
obj/loginform.o: loginform.cpp loginform.h uis_cpp/loginform.h
obj/gamewindow.o: gamewindow.cpp gamewindow.h
obj/jsbrige.o: jsbrige.cpp jsbrige.h
obj/main.o: main.cpp charselect.h loginform.h gamewindow.h

#headers
gamewindow.h: uis_cpp/gamewindow.h
charselect.h: uis_cpp/charselect.h
loginform.h: uis_cpp/loginform.h

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

LOGIC_SRC=../logic/src
CPPFLAG= --std=c++11 -lQt5Widgets -lQt5WebKit -lQt5Core -lQt5WebKitWidgets \
-lQt5Gui -lpthread \
-L. -lKastiBob_logic -I$(LOGIC_SRC) -Iinclude -Iuis_h

ifeq ($(OS),LINUX)
CPPFLAG+= -I/usr/include/x86_64-linux-gnu/qt5 -fPIC -Wl,-rpath=.
endif
obj/%.o :
	@echo "-Compile" $@
	@$(CXX) -c -Wall -o $@ $(CPPFLAG) $<


PROGRAM=KastiBobGui
ifeq ($(OS),LINUX)
	LOGIC=libKastiBob_logic.so
else
	LOGIC=KastiBob_logic.dll
endif

obj:
	mkdir -p obj
uis_h:
	mkdir -p uis_h
moc_cpp:
	mkdir -p moc_cpp
resources:
	mkdir -p resources
obj_rsc:
	mkdir -p obj_rsc
#for a lot of objects
#ld -r a.o b.o -o ab.o

all: obj uis_h moc_cpp $(PROGRAM)

RSC_FILES=$(wildcard files/*)
RSC_CPP=$(patsubst files/%,resources/%.gen.cpp,$(RSC_FILES))
RSC_RCCS=$(patsubst files/%,resources/rcc_%.gen.qrc,$(RSC_FILES))
RSC_OBJS=$(patsubst files/%,obj_rsc/%.o,$(RSC_FILES))
RSC_COMB=obj/rsc_resources_all.o

#.PRECIOUS: $(RSC_CPP) $(RSC_RCCS)

obj/rsc_resources_all.o: resources obj_rsc $(RSC_RCCS) $(RSC_CPP) $(RSC_OBJS)
	ld -r $(RSC_OBJS) -o $@
resources/rcc_%.gen.qrc:
	@echo "Generating "$@
	@echo "<RCC>\
	<qresource>\
	<file alias=\""$(patsubst resources/rcc_%.gen.qrc,%,$@)"\">\
	../files/"$(patsubst resources/rcc_%.gen.qrc,%,$@)\
	"</file>\
	</qresource>\
	</RCC>" > $@
resources/%.gen.cpp: files/%
	rcc $(patsubst resources/%.cpp,resources/rcc_%.qrc,$@) -o $@ -name $(subst /,_,$@)
obj_rsc/%.o : resources/%.gen.cpp
	@echo "-Compile "$@
	@$(CXX) -c $< -o $@  $(CPPFLAG)
MOC=jsbridge loginform runmain gamewindow charselect
MOCS=$(patsubst %,moc_%.gen,$(MOC))

OBJS=main charselect loginform gamewindow jsbridge \
		 config $(MOCS)
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
obj/main.o: src/main.cpp include/loginform.h include/charselect.h include/gamewindow.h
obj/config.o: src/config.cpp include/config.hpp $(LOGIC_SRC)/file.hpp
obj/moc_jsbridge.gen.o: moc_cpp/jsbridge.gen.cpp
obj/moc_loginform.gen.o: moc_cpp/loginform.gen.cpp
obj/moc_runmain.gen.o: moc_cpp/runmain.gen.cpp
obj/moc_gamewindow.gen.o: moc_cpp/gamewindow.gen.cpp
obj/moc_charselect.gen.o: moc_cpp/charselect.gen.cpp
#headers
include/gamewindow.h: uis_h/gamewindow.gen.h
include/charselect.h: uis_h/charselect.gen.h
include/loginform.h: uis_h/loginform.gen.h
moc_cpp/jsbridge.gen.cpp: include/jsbridge.h
moc_cpp/loginform.gen.cpp: include/loginform.h
moc_cpp/runmain.gen.cpp: include/runmain.hpp
moc_cpp/gamewindow.gen.cpp: include/gamewindow.h
moc_cpp/charselect.gen.cpp: include/charselect.h

OBJECTS=$(patsubst %,obj/%.o,$(OBJS))

$(PROGRAM): $(RSC_COMB) $(OBJECTS) $(LOGIC)
	@echo "============ Compile" $@ "=============="
	$(CXX) $^ -o $@ $(CPPFLAG)

$(LOGIC): ../logic/$(LOGIC)
	cp ../logic/$(LOGIC) .

debug: all
	gdb $(PROGRAM) -q -x gdb_start

test: all
	./$(PROGRAM)
clean:
	@(rm obj/* || true)
	@(rm obj_rsc/* || true)
	@(rm resources/* || true)
	@(rm $(PROGRAM) || true)

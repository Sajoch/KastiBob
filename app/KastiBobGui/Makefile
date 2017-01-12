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
	@$(CXX) -c $< -o $@
MOC=jsbridge
MOCS=$(patsubst %,moc_%.gen,$(MOC))

OBJS=main charselect loginform gamewindow jsbridge \
		 file spriteLoader $(MOCS)
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

$(PROGRAM): $(RSC_COMB) $(OBJECTS) $(LOGIC)
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
	@(rm obj_rsc/* || true)
	@(rm resources/* || true)
	@(rm $(PROGRAM) || true)

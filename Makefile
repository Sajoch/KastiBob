-include user.conf
CXX=$(PRE)g++
RCC=$(PRE)rcc
UIC=$(PRE)uic
LD=$(PRE)ld
AR=$(PRE)ar
MOC=$(PRE)moc

INCLUDEPATH+=inc build/ui_forms/
CXXFLAGS+=--std=c++11 -Wall -Wextra
LIBS=Qt5Widgets Qt5WebKit Qt5Core Qt5WebKitWidgets Qt5Gui pthread
PROGRAM+=build/KastiBob

ifeq ($(DEBUG),1)
CXXFLAGS+= -ggdb
endif
INCS= $(patsubst %,-I%,$(INCLUDEPATH))
CXXFLAGS+=$(INCS)
LDFLAGS+=$(INCS)
LDFLAGS+= $(patsubst %,-L%,$(LIBPATH))
LDFLAGS+= $(patsubst %,-l%,$(LIBS))
LDFLAGS+=  -Xlinker -v

#cpp files
cpp_files=$(wildcard src/*.cpp)
cpp_objects=$(patsubst src/%,build/obj/%.o,$(cpp_files))
cpp_deps=$(patsubst src/%,build/deps/%.d,$(cpp_files))
OBJS=$(cpp_objects)

#ui files
ui_files=$(wildcard ui_forms/*.ui)
ui_hpp_files=$(patsubst ui_forms/%.ui,build/ui_forms/ui_%.hpp,$(ui_files))
ui_cpp_files=$(patsubst ui_forms/%.ui,build/ui_forms/ui_%.cpp,$(ui_files))

#qrc files
rsc_files=$(wildcard resources/*)
rsc_qrc_files=$(patsubst resources/%,build/resources/qrc/%.qrc,$(rsc_files))
rsc_cpp_files=$(patsubst resources/%,build/resources/cpp/%.cpp,$(rsc_files))
rsc_obj_files=$(patsubst resources/%,build/resources/obj/%.o,$(rsc_files))
ALL_RESOURCES_ONE=build/resources/rc.a
OBJS+=$(ALL_RESOURCES_ONE)

test: run_$(PROGRAM)
debug: debug_$(PROGRAM)
all: dirs make_ui_forms make_resources make_deps_cpp
	$(MAKE) $(PROGRAM)
list-tools:
	@echo "CXX = "$(CXX)
	@echo "RCC = "$(RCC)
	@echo "UIC = "$(UIC)
	@echo "LD = "$(LD)
	@echo "AR = "$(AR)
	@echo "MOC = "$(MOC)

#Directories

.PHONY: dirs
dirs:
	@mkdir -p build
	@mkdir -p build/deps
	@mkdir -p build/obj
	@mkdir -p build/ui_forms
	@mkdir -p build/meta_objs
	@mkdir -p build/resources/obj
	@mkdir -p build/resources/qrc
	@mkdir -p build/resources/cpp

#CPP

.PHONY: make_deps_cpp
make_deps_cpp:
	$(MAKE) $(cpp_deps)
build/deps/%.cpp.d: src/%.cpp
	@echo "Make deps "$@
	@$(CXX) $(CXXFLAGS) -MM -MT build/obj/$*.cpp.o $< -o $@
build/obj/%.cpp.o:
	@echo "Complie "$@
	$(CXX) $(CXXFLAGS) -c $< -o $@
-include build/deps/*.d
$(PROGRAM): build/obj $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) -o $@

#Resources

.PHONY: make_resources
make_resources_qrc: $(rsc_qrc_files)
make_resources_cpp: $(rsc_cpp_files)
make_resources_obj: $(rsc_obj_files)
make_resources: make_resources_qrc make_resources_cpp make_resources_obj $(ALL_RESOURCES_ONE)
build/resources/qrc/%.qrc: 
	@echo "Generate rule to create "$@
	@nodejs scripts/make_qrc.js $@ resources/$*
build/resources/cpp/%.cpp: build/resources/qrc/%.qrc resources/%
	@echo "Translate "$<" to binary"
	$(RCC) $< -o $@ -name $(subst /,_,$@)
build/resources/obj/%.o: build/resources/cpp/%.cpp resources/%
	@echo "Compile resource "$@
	@$(CXX) $(CXXFLAGS) -c $< -o $@
$(ALL_RESOURCES_ONE): $(rsc_obj_files)
	@echo "Combine all resources"
	$(AR) rvs $@ $^

#UI Forms

.PHONY: make_ui_forms
make_ui_forms: $(ui_hpp_files)
build/ui_forms/ui_%.hpp: ui_forms/%.ui
	@echo "Generating "$@" using UIC"
	@$(UIC) $< -o $@

#MOCs

.PHONY: make_mobjs
make_mobjs: $(ui_cpp_files)
build/ui_forms/ui_%.cpp: build/ui_forms/ui_%.hpp
	@echo "Generating "$@" using MOC"
	$(MOC) $<

#Run

run_$(PROGRAM): all
	./$(PROGRAM)
debug_$(PROGRAM): all
	gdb $(PROGRAM)
	
#Clean
	
.PHONY: clean clean_program clean_obj_cpp clean_deps_cpp clean_ui_form
clean_program:
	@(rm $(PROGRAM) >/dev/null 2>&1 || true)
clean_obj_cpp:
	@(rm -rf build/obj/* >/dev/null 2>&1 || true)
clean_deps_cpp:
	@(rm -rf build/deps/* >/dev/null 2>&1 || true)
clean_ui_form:
	@(rm -rf build/ui_forms/* >/dev/null 2>&1 || true)
clean: 
	@(rm -rf build >/dev/null 2>&1 || true)

ifeq ($(OS),LINUX)
	CROSS_COMPILE=
	CROSS_COMPILE32=
	LOGIC_SHARED=logic_so
else ifeq ($(OS), WIN32)
	CROSS_COMPILE=i686-w64-mingw32-
	CROSS_COMPILE32=i686-w64-mingw32-
	LOGIC_SHARED=logic_dll
else
	CROSS_COMPILE=x86_64-w64-mingw32-
	CROSS_COMPILE32=i686-w64-mingw32-
	LOGIC_SHARED=logic_dll
endif
export CXX=$(CROSS_COMPILE)g++
export GCC=$(CROSS_COMPILE)gcc
export CXX32=$(CORSS_COMPILE32)g++
export GCC32=$(CORSS_COMPILE32)gcc
mbin2c:
	$(MAKE) -C bin2c all
minject: mbin2c
	$(MAKE) -C running_inject all
test_inject: minject
	$(MAKE) -C running_inject test
mdll: minject
	$(MAKE) -C KastiDll all
test_dll: mdll
	$(MAKE) -C KastiDll test
logic:
	$(MAKE) -C app/logic test
logic_dll:
	$(MAKE) -C app/logic dll
logic_so:
	$(MAKE) -C app/logic so
sprunpack:
	$(MAKE) -C app/sprunpack test
gui: $(LOGIC_SHARED)
	$(MAKE) -C app/KastiBobGui test
dgui: $(LOGIC_SHARED)
	$(MAKE) -C app/KastiBobGui debug
clean_gui:
	$(MAKE) -C app/KastiBobGui clean
clean_logic:
	$(MAKE) -C app/logic clean
clean:
	$(MAKE) -C KastiDll clean
	$(MAKE) -C running_inject clean
	$(MAKE) -C app/logic clean
	$(MAKE) -C app/KastiBobGui clean

start_kclient: kclient_v1
	cd kclient_v1; ./Kasti.exe&
kclient_v2.zip:
		wget http://web.kasteria.pl/files/kclient_v2.zip -D kclient_v2.zip
kclient_v1: kclient_v2.zip
	unzip kclient_v2.zip

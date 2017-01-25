ifeq ($(OS),LINUX)
	CROSS_COMPILE=
	CROSS_COMPILE32=
else ifeq ($(OS), WIN32)
	CROSS_COMPILE=i686-w64-mingw32-
	CROSS_COMPILE32=i686-w64-mingw32-
else
	CROSS_COMPILE=x86_64-w64-mingw32-
	CROSS_COMPILE32=i686-w64-mingw32-
endif
export CXX=$(CROSS_COMPILE)g++
export GCC=$(CROSS_COMPILE)gcc
export CXX32=$(CORSS_COMPILE32)g++
export GCC32=$(CORSS_COMPILE32)gcc
mbin2c:
	make -C bin2c all
minject: mbin2c
	make -C running_inject all
test_inject: minject
	make -C running_inject test
mdll: minject
	make -C KastiDll all
test_dll: mdll
	make -C KastiDll test
logic:
	make -C app/logic test
sprunpack:
	make -C app/sprunpack test
gui:
	make -C app/logic dll
	make -C app/KastiBobGui test
dgui:
	make -C app/logic dll
	make -C app/KastiBobGui debug
clean_gui:
	make -C app/KastiBobGui clean
clean:
	make -C KastiDll clean
	make -C running_inject clean
	make -C app/logic clean
	make -C app/KastiBobGui clean

start_kclient: kclient_v1
	cd kclient_v1; ./Kasti.exe&
kclient_v2.zip:
		wget http://web.kasteria.pl/files/kclient_v2.zip -D kclient_v2.zip
kclient_v1: kclient_v2.zip
	unzip kclient_v2.zip

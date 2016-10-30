export CXX=x86_64-w64-mingw32-g++
export GCC=x86_64-w64-mingw32-gcc
export CXX32=i686-w64-mingw32-g++
export GCC32=i686-w64-mingw32-gcc
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

clean:
	make -C KastiDll clean
	make -C running_inject clean

start_kclient: kclient_v1
	cd kclient_v1; ./Kasti.exe&
kclient_v2.zip:
		wget http://web.kasteria.pl/files/kclient_v2.zip -D kclient_v2.zip
kclient_v1: kclient_v2.zip
	unzip kclient_v2.zip

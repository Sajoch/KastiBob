#include <string>
#include <windows.h>
#include <map>
#include <vector>
/*
typedef struct _IMAGE_RELOCATION {
      __C89_NAMELESS union {
        DWORD VirtualAddress;
        DWORD RelocCount;
      } DUMMYUNIONNAME;
      DWORD SymbolTableIndex;
      WORD Type;
    } IMAGE_RELOCATION;
    typedef IMAGE_RELOCATION UNALIGNED *PIMAGE_RELOCATION;


typedef struct _IMAGE_SYMBOL {
	union {
		BYTE ShortName[8];
		struct {
			DWORD Short;
			DWORD Long;
		} Name;
		DWORD LongName[2];
	} N;
	DWORD Value;
	SHORT SectionNumber;
	WORD Type;
	BYTE StorageClass;
	BYTE NumberOfAuxSymbols;
} IMAGE_SYMBOL;
typedef IMAGE_SYMBOL UNALIGNED *PIMAGE_SYMBOL;

};
*/
struct IMAGE_REAL_SYMBOL{
	bool good;
	unsigned long offset;
	std::string name;
	unsigned long value;
	unsigned int section;
};
class ObjectFile{
	//std::string data;
	std::string image;
	unsigned long base;

	IMAGE_FILE_HEADER header;
	std::vector<IMAGE_SECTION_HEADER> sections;
	//std::vector<IMAGE_SYMBOL> symbols;
	std::vector<IMAGE_RELOCATION> relocations;
	bool done;

	std::vector<unsigned long> rsecs;
	std::vector<IMAGE_REAL_SYMBOL> rsyms;

public:
	ObjectFile(unsigned const char* data, unsigned long len);
	unsigned long size();
	const char* map();
	void* getAddress(std::string name);
	void remap(void* baseaddress);
	void setAddress(std::string name, unsigned long address);
};

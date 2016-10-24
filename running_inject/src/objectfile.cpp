#include "objectfile.hpp"
#include <vector>
#include <map>
#include <iostream>
using namespace std;


ObjectFile::ObjectFile(unsigned const char* dt, unsigned long len){
	done=false;
	string buf((char*)dt,len);
	IMAGE_SECTION_HEADER sec;
	std::map <size_t, size_t> relocation_pos_size;
	string now_need;
	size_t pos, size_buf;
	int state = 0;
	pos = 0;
	size_buf = sizeof(IMAGE_FILE_HEADER);
	size_t index;
	size_t count_relocations;
	size_t string_table;

	while (!done) {
		if (buf.size() < (pos+size_buf)) {
			cout<<"not enough data"<<endl;
			return;
		}
		now_need = buf.substr(pos,size_buf);
		pos += size_buf;
		switch (state) {
			case 0://image_file_header
				//cout<<"image_file_header"<<endl;
				memcpy(&header, &now_need[0], size_buf);
				state = 1;
				size_buf = sizeof(IMAGE_SECTION_HEADER);
			break;
			case 1://image_section_header
				//cout<<"image_section_header"<<endl;
				memcpy(&sec, &now_need[0], size_buf);
				count_relocations += sec.NumberOfRelocations;
				sections.push_back(sec);
				if (sections.size() >= header.NumberOfSections) {
					state = 2;
					size_buf = 0;
				}
			break;
			case 2://start_section
				//cout<<"start_section"<<endl;
				index = 0;
				if(index < sections.size()){
					pos = sections[0].PointerToRawData;
					if (pos == 0)
						size_buf = 0;
					else
						size_buf = sections[0].SizeOfRawData;
				}
				state = 3;
			break;
			case 3://section
				if(index < sections.size()){
						//cout<<"section pos "<<(void*)pos<<" sbuf "<<(void*)size_buf<<" "<<index<<"/"<<sections.size()<<endl;
						rsecs.push_back(image.size());
						if (sections[index].PointerToRawData == 0) {
							now_need = string(sections[index].SizeOfRawData, 0);
						}
						if (sections[index].PointerToRelocations != 0 && sections[index].NumberOfRelocations > 0) {
							relocation_pos_size[sections[index].PointerToRelocations] = sections[index].NumberOfRelocations + 1;
						}
						image.append(now_need);
						index++;
				}
				pos = 0;
				size_buf = 0;
				state = 4;
				if (index < sections.size()) {
					pos = sections[index].PointerToRawData;
					size_buf = sections[index].SizeOfRawData;
					state = 3;
				}
			break;
			case 4:{//start_relocation
				std::map <size_t, size_t>::iterator fr;
				if (relocation_pos_size.size() > 0 && (fr=relocation_pos_size.begin())->second > 0) {
					state = 5;
					pos = fr->first;
					size_buf = sizeof(IMAGE_RELOCATION);
					fr->second--;
				} else {
					state = 6;
				}
			}break;
			case 5:{//relocation
				std::map <size_t, size_t>::iterator fr;
				if (relocation_pos_size.size() > 0 && (fr=relocation_pos_size.begin())->second > 0) {
					IMAGE_RELOCATION rel;
					memcpy(&rel, &now_need[0], size_buf);
					//cout<<"relocation"<<endl;
					relocations.push_back(rel);
					fr->second--;
					if(fr->second == 0){
						relocation_pos_size.erase(fr);
					}
				} else {
					pos = 0;
					size_buf = 0;
					state = 6;
				}
			}break;
			case 6://start_symbols
				//cout<<"start symbol"<<endl;
				if (rsyms.size() < header.NumberOfSymbols) {
					pos = header.PointerToSymbolTable;
					size_buf = sizeof(IMAGE_SYMBOL);
					state = 8;
					index = 1;
				} else {
					pos = 0;
					size_buf = 0;
					state = 9;
				}
			break;
			case 8:{//symbols
				//cout<<"symbol"<<endl;
				if (rsyms.size() < header.NumberOfSymbols) {
					IMAGE_SYMBOL sym;
					IMAGE_REAL_SYMBOL rsym;
					memcpy(&sym, &now_need[0], size_buf);
					if(index==0){
						if (sym.N.LongName[0]==0){
							rsym.offset = sym.N.LongName[1];
							rsym.name = "";
						} else {
							rsym.offset = 0;
							rsym.name = (char*)sym.N.ShortName;
						}
						rsym.value = sym.Value;
						rsym.section = (unsigned short)sym.SectionNumber;
						index = (size_t)(unsigned char)sym.NumberOfAuxSymbols;
						rsym.good = true;
					}else{
						rsym.good = false;
						index--;
					}
					rsyms.push_back(rsym);
				}else{
					string_table = pos - size_buf;
					size_buf = 0;
					state = 9;
				}
			}break;
			case 9://start string table
				index = 0;
				state = 10;
			case 10:
				//cout<<"index "<<index<<endl;
				if (index < rsyms.size()) {
					if (rsyms[index].good && rsyms[index].offset != 0 && rsyms[index].name.empty()){
						pos = string_table + rsyms[index].offset;
						size_buf = 1;
						state = 11;
					}else{
						index++;
					}
				} else {
					done = true;
				}
			break;
			case 11:{//read string table
				//cout<<"read at "<<pos<<endl;
				char c = now_need[0];
				size_buf = 1;
				if(c==0){
					//cout<<"close"<<endl;
					index++;
					state = 10;
					pos = 0;
					size_buf = 0;
				}else{
					rsyms[index].name+=c;
				}
			}break;
		}
	}
}
unsigned long ObjectFile::size(){
	return image.size();
}
const char* ObjectFile::map(){
	return image.c_str();
}
void ObjectFile::remap(void* _base){
	base=(size_t)_base;
	for(size_t i=0;i<relocations.size();i++){
		switch(relocations[i].Type){
			case 0x06:{
				//cout<<"rel"<<endl;
				unsigned long d=rsecs[rsyms[relocations[i].SymbolTableIndex].section-1]+
					rsyms[relocations[i].SymbolTableIndex].value;
				unsigned long b;
				memcpy(&b,&image[relocations[i].VirtualAddress],4);
				b+=d+base;
				memcpy(&image[relocations[i].VirtualAddress],&b,4);
				//cout<<"symbol "<<relocations[i].SymbolTableIndex<<endl;
				//cout<<"add "<<(void*)d<<endl;
				//cout<<"at "<<(void*)relocations[i].VirtualAddress<<endl;
			}break;
			case 0x14:
				cout<<"dir"<<endl;

			break;
		}

	}
	for(size_t i=0;i<rsyms.size();i++){
		//cout<<i<<" "<<rsyms[i].name<<" value "<<rsyms[i].value<<" sec "<<rsyms[i].section<<endl;
	}
}
void* ObjectFile::getAddress(std::string name){
	for(size_t i=0;i<rsyms.size();i++){
		if(rsyms[i].name==name){
			return (void*)(base+rsecs[rsyms[i].section-1]+rsyms[i].value);
		}
		//cout<<i<<" "<<rsyms[i].name<<" value "<<rsyms[i].value<<" sec "<<rsyms[i].section<<endl;
	}
	return 0;
	//return (void*)(((unsigned long)base)+0xE6);
}
void ObjectFile::setAddress(std::string name, size_t address){
	for(size_t i=0;i<rsyms.size();i++){
		if(rsyms[i].name==name){
			memcpy(&image[rsecs[rsyms[i].section-1]+rsyms[i].value], &address, sizeof(size_t));
			//return (void*)(((unsigned long)base)+rsecs[rsyms[i].section-1]+rsyms[i].value);
		}
	}
}

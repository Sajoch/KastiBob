#include "objectfile.hpp"
#include <vector>
#include <iostream>
using namespace std;


ObjectFile::ObjectFile(unsigned const char* dt, unsigned long len){
	done=false;
	data.append((char*)dt,len);
	string buf((char*)dt,len);
	size_t d;
	d=sizeof(IMAGE_FILE_HEADER);
	if(buf.size()>=d){
		memcpy(&header, buf.substr(0,d).data(), d);
		buf.erase(0,d);
	}else{
		cout<<"not enough bytes to read header"<<endl;
		return;
	}
	size_t string_table=header.PointerToSymbolTable;
	header.PointerToSymbolTable-=d;
	while(rsyms.size()<header.NumberOfSymbols){
		//cout<<(void*)buf[header.PointerToSymbolTable]<<(void*)buf[header.PointerToSymbolTable+1]<<endl;
		IMAGE_SYMBOL sym;
		d=18;//sizeof(IMAGE_SYMBOL);
		string_table+=d;
		if(buf.size()>=d){
			memcpy(&sym, buf.substr(header.PointerToSymbolTable,d).data(), d);
			buf.erase(header.PointerToSymbolTable,d);
		}else{
			cout<<"not enough bytes to read symbol "<<rsyms.size()<<"/"<<header.NumberOfSymbols<<endl;
			return;
		}
		IMAGE_REAL_SYMBOL trs;
		if(sym.N.LongName[0]==0){
			trs.offset=sym.N.LongName[1];
			trs.name="";
		}else{
			trs.offset=0;
			trs.name=(char*)sym.N.ShortName;
		}
		trs.value=sym.Value;
		trs.section=(unsigned short)sym.SectionNumber;
		rsyms.push_back(trs);
		for(int aux=0;aux<(int)sym.NumberOfAuxSymbols;aux++){
			IMAGE_REAL_SYMBOL symc={0};
			switch(sym.StorageClass){
				case 0x67:{
					string tmp;
					string t;
					do{
						t=buf.substr(header.PointerToSymbolTable,6);
						buf.erase(header.PointerToSymbolTable,6);
						tmp+=t;
					}while(t[0]!=0 && buf.size()>=6);
					string_table+=tmp.size();
					rsyms.push_back(symc);
				}break;
				case 0x02:
					buf.erase(header.PointerToSymbolTable,18);
					string_table+=18;
					rsyms.push_back(symc);
				break;
				case 0x03:
					buf.erase(header.PointerToSymbolTable,18);
					string_table+=18;
					rsyms.push_back(symc);
				break;
			}
		}
	}
	buf.erase(header.PointerToSymbolTable,len-string_table);
	for(size_t i=0;i<rsyms.size();i++){
		if(rsyms[i].name.empty() && rsyms[i].offset!=0){
			char* cp = (char*)&dt[string_table+rsyms[i].offset];
			rsyms[i].name=cp;
		}
	}
	size_t deleted_space=0;
	for(unsigned int i=0;i<header.NumberOfSections;i++){
		IMAGE_SECTION_HEADER sec;
		d=sizeof(IMAGE_SECTION_HEADER);
		if(buf.size()>=d){
			memcpy(&sec, buf.substr(0,d).data(), d);
			buf.erase(0,d);
		}else{
			cout<<"not enough bytes to read section "<<i<<"/"<<header.NumberOfSections<<endl;
			return;
		}
		deleted_space+=sec.SizeOfRawData;
		sections.push_back(sec);
	}
	buf.erase(0,deleted_space);
	d=sizeof(IMAGE_RELOCATION);
	while(buf.size()>=d){
		IMAGE_RELOCATION rel;
		if(buf.size()>=d){
			memcpy(&rel, buf.substr(0,d).data(), d);
			buf.erase(0,d);
		}else{
			cout<<"not enough bytes to read relocation"<<endl;
			return;
		}
		relocations.push_back(rel);
	}
	for(size_t i=0;i<sections.size();i++){
		rsecs.push_back(image.size());
		//cout<<"sec "<<i<<" = "<<image.size()<<endl;
		if (sections[i].PointerToRawData!=0 && sections[i].SizeOfRawData!=0) {
			//image.append(dt[sections[i].PointerToRawData], sections[i].SizeOfRawData);
			for(size_t di=0;di<sections[i].SizeOfRawData;di++){
				image.push_back(data[sections[i].PointerToRawData+di]);
			}
		}
	}
	done=true;
}
unsigned long ObjectFile::size(){
	return image.size();
}
const char* ObjectFile::map(){
	return image.c_str();
}
void ObjectFile::remap(void* _base){
	base=(unsigned long)_base;
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
			return (void*)(((unsigned long)base)+rsecs[rsyms[i].section-1]+rsyms[i].value);
		}
		//cout<<i<<" "<<rsyms[i].name<<" value "<<rsyms[i].value<<" sec "<<rsyms[i].section<<endl;
	}
	return 0;
	//return (void*)(((unsigned long)base)+0xE6);
}

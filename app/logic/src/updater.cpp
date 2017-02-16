#include "updater.hpp"
#include <iostream>
#include <fstream>
#define POCO_WIN32_UTF8
#include <Poco/MD5Engine.h>
#include <Poco/DigestStream.h>
#include <Poco/StreamCopier.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/URI.h>
#include <cmath>

using namespace std;

bool Updater::compare(std::string md5_a, std::string md5_b){
	return md5_a == md5_b;
}
std::string Updater::getFileName(Updater_File type){
	switch(type){
		case Updater_File::FILE_SPR:
			return "Tibia.spr";
		case Updater_File::FILE_DAT:
			return "Tibia.dat";
		case Updater_File::FILE_PIC:
			return "Tibia.pic";
		case Updater_File::FILE_EXE:
			return "Tibia.exe";
		case Updater_File::FILE_DLL:
			return "Tibia.dll";
		case Updater_File::FILE_CAMEXE:
			return "";
		default:
			break;
	}
	return "";
}
Updater::~Updater(){
	//close thread
}
Updater::Updater(std::string chUrl, std::string dlUrl){
	checkingUrl = chUrl;
	downloadUrl = dlUrl;
	std::string retBuffer;
	Poco::URI link(chUrl);
	Poco::Net::HTTPClientSession ses(link.getHost());
	Poco::Net::HTTPRequest req("GET", link.getPath());
	Poco::Net::HTTPResponse res;
	ses.sendRequest(req);
	std::istream& out = ses.receiveResponse(res);
	while(!out.eof()){
		retBuffer.resize(retBuffer.size() + 512);
		out.read(&retBuffer[retBuffer.size()-512], 512);
	}
	std::string _hash;
	Updater_File now = Updater_File::FILE_SPR;
	char c;
	size_t l = retBuffer.size();
	for(size_t i=0;i<l;i++){
		c = retBuffer[i];
		if(c == '\n'){
			cout<<"hash "<<_hash<<endl;
			hash[now] = _hash;
			_hash.clear();
			switch(now){
				case Updater_File::FILE_SPR:
					now = Updater_File::FILE_DAT;
					break;
				case Updater_File::FILE_DAT:
					now = Updater_File::FILE_PIC;
					break;
				case Updater_File::FILE_PIC:
					now = Updater_File::FILE_EXE;
					break;
				case Updater_File::FILE_EXE:
					now = Updater_File::FILE_DLL;
					break;
				case Updater_File::FILE_DLL:
					now = Updater_File::FILE_CAMEXE;
					break;
				default:
					break;
			}
		}else{
			_hash += c;
		}
	}
	//onCheck();
}
void Updater::afterDone(std::function<void()> func){
	onEnd = func;
}
void Updater::afterChangeState(std::function<void(std::string dl, int state)> func){
	onChangeState = func;
}
void replace(std::string& str, std::vector<std::string>& tab){
	size_t l = str.size();
	size_t bc;
	size_t num=0;
	bool started = false;
	uint8_t ch;
	for(size_t i=0;i<l;i++){
		ch = str[i];
		if(ch == '$' && !started){
			bc = i;
			started = true;
		}else if(started){
			if(ch>='0' && ch<='9'){
				num *= 10;
				num += (uint32_t)(ch-'0');
			}else if(ch=='$'){
				str.erase(str.begin()+i);
				started = false;
			}else{
				num -= 1;
				started = false;
				if(num < tab.size()){
					std::string& arg = tab[num];
					str.replace(bc, (i-bc), arg);
					i += arg.size();
					l += arg.size();
				}
			}
		}
	}
	if(started){
		num -= 1;
		if(num < tab.size()){
			std::string& arg = tab[num];
			str.replace(bc, (str.size()-bc), arg);
		}
	}
}
std::string Updater::getMD5(std::string path){
	std::ifstream filestr(path, ios::binary);
	if(!filestr.good()){
		return "";
	}
	Poco::MD5Engine md5;
	Poco::DigestOutputStream outstr(md5);
	Poco::StreamCopier::copyStream(filestr, outstr);
  return Poco::DigestEngine::digestToHex(md5.digest());
}
void Updater::check(std::string path, Updater_File type){
	if(hash[type].empty()){
		return;
	}
	std::string md5 = getMD5(path);
	if(compare(md5, hash[type])){
		return;
	}
	std::string url = downloadUrl;
	std::string file = getFileName(type);
	std::vector<std::string> args;
	if(file.empty()){
		return;
	}
	fstream fout(path, ios::trunc|ios::binary|ios::out);
	if(!fout.is_open()){
		return;
	}
	args.push_back(file);
	replace(url, args);
	
	Poco::URI link(url);
	Poco::Net::HTTPClientSession ses(link.getHost());
	Poco::Net::HTTPRequest req("GET", link.getPath());
	Poco::Net::HTTPResponse res;
	ses.sendRequest(req);
	std::istream& out = ses.receiveResponse(res);
	size_t length = res.getContentLength();
	int percent;
	size_t clen = 0;
	size_t rlen;
	std::string tmp;
	tmp.resize(512);
	while(!out.eof() && clen < length){
		rlen = length - clen;
		if(rlen > 512){
			rlen = 512;
		}
		out.read(&tmp[0], rlen);
		clen += rlen;
		fout.write(&tmp[0], rlen);
		int npercent = floor((double)clen / (double)length * 100);
		if(percent != npercent){
			percent = npercent;
			onChangeState(file, percent);
		}
	}
	
}
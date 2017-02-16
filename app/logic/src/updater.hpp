#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <mutex>
#include <functional>
#include "dll.h"
enum class Updater_File{
	FILE_NONE,
	FILE_SPR,
	FILE_DAT,
	FILE_PIC,
	FILE_EXE,
	FILE_DLL,
	FILE_CAMEXE
};

class API Updater{
	std::function<void(void)> onEnd;
	std::function<void(std::string, int)> onChangeState;
	std::string checkingUrl;
	std::string downloadUrl;
	std::mutex downloadState;
	std::map<Updater_File, std::string> hash;
	bool compare(std::string md5_a, std::string md5_b);
	std::string getFileName(Updater_File type);
	std::string getMD5(std::string path);
public:
	Updater(std::string chUrl, std::string dlUrl);
	~Updater();
	void afterDone(std::function<void()> func);
	void afterChangeState(std::function<void(std::string dl, int state)> func);
	void check(std::string path, Updater_File type);
};
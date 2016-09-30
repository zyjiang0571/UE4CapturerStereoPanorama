#ifndef FStereoPanoramaManagerBase_H
#define FStereoPanoramaManagerBase_H

#include <vector>
#include <math.h>
#include <map>
#include <string>
#include <sstream>
#include "Engine.h"

using namespace std;

// Calc String Hash Value
static constexpr size_t HASH_STRING_PIECE(const char *string_piece, size_t hashNum = 0) {
	return *string_piece ? HASH_STRING_PIECE(string_piece + 1, (hashNum * 131) + *string_piece) : hashNum;
}
static constexpr size_t operator "" _HASH(const char *string_pice, size_t) {
	return HASH_STRING_PIECE(string_pice);
}
static size_t hashNum(const string &str) {
	return HASH_STRING_PIECE(str.c_str());
}

class FStereoPanoramaManagerBase {
public:
	FStereoPanoramaManagerBase(){}
	// 通过接收到的参数修改ArgsMap的值
	void FStereoPanoramaManagerBase::setArgsMap(const vector<string>& args) 
	{
		for (vector<string>::const_iterator iterConut = args.cbegin(); iterConut < args.cend(); ++iterConut) {
			if (argsMap.find(iterConut->c_str()) != argsMap.end()) {
				switch (hashNum(*iterConut)) {
					case "-b"_HASH: {
						argsMap["-b"] = (iterConut + 1)->c_str();
						++iterConut;
						break;
					}
					case "-e"_HASH: {
						argsMap["-e"] = (iterConut + 1)->c_str();
						++iterConut;
						break;
					}
					case "-p"_HASH: {
						argsMap["-p"] = (iterConut + 1)->c_str();
						++iterConut;
						break;
					}
					case "-r"_HASH: {
						if (resolutionMap.find((iterConut + 1)->c_str()) != resolutionMap.end()) {
							argsMap["-r"] = (iterConut + 1)->c_str();
							++iterConut;
						}
						break;
					}
					case "-bo"_HASH: {
						switch (hashNum(*(iterConut+1)))
						{
							case "true"_HASH: {
								argsMap["-bo"] = "1";
								++iterConut;
								break;
							}
							case "false"_HASH: {
								argsMap["-bo"] = "0";
								++iterConut;
								break;
							}
						}
						break;
					}
					case "-fps"_HASH: {
						argsMap["-fps"] = (iterConut + 1)->c_str();
						++iterConut;
						break;
					}
					case "-t"_HASH: {
						argsMap["-t"] = (iterConut + 1)->c_str();
						unsigned int second=mergeMinToSecond(*(iterConut + 1));
						argsMap["-e"] = int2str(second * FCString::Atoi(*argsMap["-fps"])).c_str();
						++iterConut;
						break;
					}
					case "-bt"_HASH: {
						argsMap["-bt"] = (iterConut + 1)->c_str();
						unsigned int second = mergeMinToSecond(*(iterConut + 1));
						argsMap["-b"] = int2str(second * FCString::Atoi(*argsMap["-fps"])).c_str();
						++iterConut;
						break;
					}
					case "-et"_HASH: {
						argsMap["-et"] = (iterConut + 1)->c_str();
						unsigned int second = mergeMinToSecond(*(iterConut + 1));
						argsMap["-e"] = int2str(second * FCString::Atoi(*argsMap["-fps"])).c_str();
						++iterConut;
						break;
					}
				}
			}
		}
	}
	//char* ConvertToCCP(FString str)
	//{
	//	string t = TCHAR_TO_UTF8(*str);
	//	char * returnvalue = (char *)malloc(sizeof(char) * (t.length() + 1));
	//	strncpy(returnvalue, t.c_str(), t.length());
	//	return returnvalue;
	//}
protected:
	virtual void init_CombineAtlasesOnOutput() = 0;
	virtual void DisableBinoculusOutput(const TArray<FString>& Args) = 0;
//public:
	// 可接受参数
	// -p	-----> outputDir : path -p X:/ The element default value is FPaths::GameSavedDir().it is /Projects/Saved/StereoPanorama
	// -r	-----> resolution : -r 4096,The element default value is 4096p
	// -bo	-----> binoculus output : -b false,The element default value is true.
	// -b   -----> begin Frame: Default is 0.if -b!=0,is "-b" Frame to "-e" Frame
	// -e   -----> end Frame: Default is 0.if -e!=0,is "-b" Frame to "-e" Frame
	// -fps -----> fps Arg : -fps=30 The element default value is 30f/s
	// timer Args
	// Do not mix with -b/-e and -t/-bt/-et 
	// -t	-----> time : -t 2.30 (begin frame is 0 to end frame 2.30*fps).The element default value is 0.The -fps default value is 30.
	// -bt  -----> -bt is begin time.Modify -bt equivalent to modify -b(time(second)*fps).
	// -et  -----> -et is end time.Modify -et equivalent to modify -e
	map<FString, FString> argsMap = { { "-b","0" },
	 								  { "-e","0" },
									  { "-p","" },
									  { "-r","4k" },
									  { "-bo","1" },
									  { "-fps","30.0"},
									  { "-t","0.0"},
									  { "-bt","0.0" },
									  { "-et","0.0" } };
protected:
	// 通过ArgsMap接收参数(xP)来决定输出的分辨率(关联)
	map<FString, vector<FString>> resolutionMap = { {"480", {{"960"}, {"480"}}},
													{"720", {{"1440"},{"720"}}},
													{"1080",{{"2160"},{"1080"}}},
													{"2k",	{{"2880"},{"1440"}}},
													{"4k",	{{"4096"},{"2048"}}}};
private:
	unsigned int mergeMinToSecond(string timer) {
		unsigned int secSum = 0;
		if (timer.find(":") != string::npos) {
			auto semicolonIndex = timer.find(":");
			string min(timer.begin(), timer.begin() + semicolonIndex);
			string sec(timer.begin() + semicolonIndex + 1, timer.end());
			secSum = stoi(min) * 60 + stoi(sec);
		}
		else {
			secSum = stoi(timer);
			return secSum;
		}
		return secSum;
	}
	string int2str(int intVal) {
		string str;
		stringstream strStream(str);
		strStream << intVal;
		return strStream.str();
	}
};
#endif
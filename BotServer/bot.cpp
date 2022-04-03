// CPPBot.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
#include <fstream>
#include <future>
#include <thread>
#include <chrono>
#include "corefunc.h"
#include "userfunc.h"
#include "json.hpp"
#include <string>
#include <windows.h>
#include <direct.h>
#define GetCurrentDir _getcwd

using namespace std;
using json = nlohmann::json;

vector<GrowtopiaBot> bots;

inline bool exists_test(const string& name) {
	ifstream f(name.c_str());
	return f.good();
}
void bot_loop() {
	GrowtopiaBot bot = {
		"RaidedByArtemis", "RaidedByArtemis"
	};
	bot.userInit();
	bot.eventLoop();
	bot.userLoop();
}
vector<thread> threads;
int main() {
	cout << "GrowtopiaBot v1.0 [Not included QT]! by GrowtopiaNoobs and DrOreo002" << endl;
	char cCurrentPath[FILENAME_MAX];

	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		return errno;
	}

	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
	string botDataPath = cCurrentPath + string("\\bot.json");

	if (!exists_test(botDataPath)) {
		cout << "Cannot find bot data on that path!. Stuck?, please read README.md" << endl;
		return 0;
	}
	cout << "Loading bot data on path (" << botDataPath << ")" << endl;

	ifstream i(botDataPath);
	json j;
	i >> j;
	SERVER_HOST = j["server_host"].get<string>();
	botmeta = j["bot_meta"].get<string>();
	SERVER_PORT = j["server_port"].get<int>();

	GrowtopiaBot bot = {
		j["username"], j["password"]
	};
	cout << "------------------------" << endl;
	cout << "Bot loaded!. Using username " << j["username"].get<string>() << ", With owner " + j["ownerUsername"].get<string>() << endl;

	bot.gameVersion = j["gameVersion"].get<string>();
	bot.worldName = j["targetWorld"].get<string>();
	bot.ownerUsername = j["ownerUsername"].get<string>();
	init();
	for (int i = 0; i < 100; i++) threads.push_back(std::thread(bot_loop));
	while (true) {}
}

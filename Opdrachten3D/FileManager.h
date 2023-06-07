#pragma once
#include <iostream>
#include <fstream>

class FileManager {
private:
	std::string path;
public:
	FileManager(std::string fileName);
	~FileManager();
	bool readActivePlayer();
	void writeActivePlayer(bool activePlayer);
};
#include "FileManager.h"

FileManager::FileManager(std::string fileName) {
	try {
		std::fstream myfile;
		myfile.open(fileName);
		std::cout << "Found file \"" << fileName << "\"." << std::endl;
		myfile.close();
		this->path = fileName;
	}
	catch (const std::exception& ex) {
		std::cout << "Couldn't find file \"" << fileName << "\"." << std::endl;
		exit(-1);
	}
}

FileManager::~FileManager() {

}

bool FileManager::readActivePlayer() {
	std::ifstream file;
	bool activePlayer;
	if (!file.is_open())
		file.open(path);
	file >> activePlayer;
	file.close();
	return activePlayer;
}

void FileManager::writeActivePlayer(bool activePlayer) {
	std::ofstream file;
	if (!file.is_open())
		file.open(path);
	file << activePlayer;
	file.close();
}
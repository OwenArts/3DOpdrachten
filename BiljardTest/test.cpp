#include "pch.h"
#include <chrono>
#include <ctime>
#include <string>
#include "FileManager.cpp"

class TestResults
{
public:
	TestResults(const std::string& path);
	~TestResults();
	void WriteResult(const std::string& testCase, const std::string& testName, bool passed);
	const std::string path;
};

TestResults::TestResults(const std::string& path) : path(path)
{
}

TestResults::~TestResults()
{
}

void TestResults::WriteResult(const std::string& testCase, const std::string& testName, bool passed) {
	std::ofstream file;
	auto now = std::chrono::system_clock::now();
	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
	std::stringstream time;
	
	time << std::put_time(std::localtime(&currentTime), "%d-%m-%Y-%H-%M-%S");
	file.open(path, std::ios::app); // Open the file in append mode

	if (file.is_open()) {
		file << '[' << time.str() << "] " << testCase << ' ' << testName << ' ' << (passed ? "Passed" : "Failed") << '\n';
		file.close();
	}
	else {
		// Handle the case when the file couldn't be opened
		std::cout << "Unable to open the file: " << path << std::endl;
	}
}

FileManager* manager = new FileManager("TestFile.txt");
TestResults* results = new TestResults("Results.txt");

TEST(FileManagerTest, WriteFile) {
	manager->writeActivePlayer(true);
	results->WriteResult("FileManagerTest", "WriteFile", (manager->readActivePlayer() == 1));
	EXPECT_EQ(manager->readActivePlayer(), 1);
}

TEST(FileManagerTest, ReadFile) {
	manager->writeActivePlayer(false);
	EXPECT_EQ(manager->readActivePlayer(), 0);
	results->WriteResult("FileManagerTest", "ReadFile0", (manager->readActivePlayer() == 0));
	manager->writeActivePlayer(true);
	EXPECT_EQ(manager->readActivePlayer(), 1);
	results->WriteResult("FileManagerTest", "ReadFile1", (manager->readActivePlayer() == 1));
	manager->writeActivePlayer(false);
	EXPECT_EQ(manager->readActivePlayer(), 0);
	results->WriteResult("FileManagerTest", "ReadFile2", (manager->readActivePlayer() == 0));
}
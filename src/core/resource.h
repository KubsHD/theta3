#pragma once

#include <string>
#include <fstream>
#include <iostream>

class Resource
{
public:
	static std::string read_file(String filePath) {
		std::string content;
		std::ifstream fileStream(filePath, std::ios::in);

		if (!fileStream.is_open()) {
			std::cout << "file not found! " << filePath << std::endl;
			return "";
		}

		std::string line = "";
		while (!fileStream.eof()) {
			std::getline(fileStream, line);
			content.append(line + "\n");
		}

		fileStream.close();
		return content;
	}
};
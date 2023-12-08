#pragma once 


#include <string>
#include <fstream>
#include <vector>

namespace utils {
	namespace file {
		inline std::string removeSpaces(std::string s) {
			std::string tmp(s);
			tmp.erase(std::remove(tmp.begin(), tmp.end(), ' '), tmp.end());
			return tmp;
		}

		inline std::vector<char> ReadAllBytes(std::string filename)
		{
			std::ifstream ifs((filename), std::ios::binary | std::ios::ate);
			std::ifstream::pos_type pos = ifs.tellg();

			std::vector<char>  result(pos);

			if (result.size() == 0)
				return result;

			ifs.seekg(0, std::ios::beg);
			ifs.read(&result[0], pos);

			ifs.close();

			return result;
		}
	}
}
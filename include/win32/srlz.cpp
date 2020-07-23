#include "srlz.h"

namespace srlz {

	void write(std::ofstream& os, std::string& value)
	{
		auto size = value.size();
		os.write(reinterpret_cast<char*>(&size), sizeof(size));
		for (auto i = 0U; i < size; i++)
			os.write(&value[i], sizeof(char));
	}

	void read(std::ifstream &is, std::string &value) {
		auto size = 0U;
		is.read(reinterpret_cast<char*>(&size), sizeof(size));
		char ch;
		for (auto i = 0U; i < size; i++) {
			is.read(&ch, sizeof(char));
			value.push_back(ch);
		}
	}
}

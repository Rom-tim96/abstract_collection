#include "srlz.h"
#include <iostream>
#include <termlib.h>

namespace srlz {

	void write(std::ofstream& os, const std::string& value)
	{
		std::size_t size = value.size();
		os.write(reinterpret_cast<char*>(&size), sizeof(size));
		for (auto i = 0U; i < size; i++)
			os.write(&value[i], sizeof(char));
	}

	void read(std::ifstream &is, std::string &value) {
				
		std::size_t size = 0;
		is.read(reinterpret_cast<char*>(&size), sizeof(size));
		
		char ch;
		for (size_t i = 0; i < size; i++) {
			is.read(&ch, sizeof(char));
			value.push_back(ch);
		}
	}
}

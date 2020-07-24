#include <string>
#include <fstream>

#ifndef SRLZ
#define SRLZ

namespace srlz {

	void write(std::ofstream& os, const std::string& value);
	void read(std::ifstream &is, std::string &value);
}

	
#endif // !SRLZ

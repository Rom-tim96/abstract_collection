#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

#include "termlib.h"
#include "srlz.h"

class Position {

	unsigned int id;
	std::string name;

public:

	static const int NAME_LENGTH = 20;
	static unsigned int count;

	Position() {

		std::cout << "Enter name: ";
		std::cin >> std::setw(NAME_LENGTH) >> name;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		id = count++;
	}

	Position(std::string _name, const unsigned int _id){
		name = _name; id = _id;
	}

	static void displayByName(std::vector<Position*> positions) {

		if (auto posCount = positions.size()) {
			std::string toSearch;
			std::cout << "Enter name to search: ";
			std::cin >> std::setw(Position::NAME_LENGTH) >> toSearch;
			std::cout << std::endl;

			std::vector<Position*> foundPos;
			for (auto i = 0U; i < posCount; ++i) {
				if (positions[i]->getName() == toSearch) {
					foundPos.push_back(positions[i]);
				}
			}

			if (auto foundCount = foundPos.size())
				Position::print(foundPos);
			else
				std::cout << "No positions found" << std::endl;
		} else
			std::cout << "List is empty.";
	}

	static void print(std::vector<Position*> positions) {

		std::cout << " " << std::setw(3) << "#" << " | " << std::setw(Position::NAME_LENGTH) << "Name" << " | " << std::endl;
		for (unsigned int i = 0U, printCount = positions.size(); i < printCount; ++i)
			std::cout << " " << std::setw(3) << positions[i]->getId() << " | " << std::setw(Position::NAME_LENGTH) << positions[i]->getName() << " | " << std::endl;

	}

	unsigned int getId() const {
		return id;
	}

	std::string getName() {
		return name;
	}

};
unsigned int Position::count = 0;

int main() {

	std::vector<Position*> allPos;
	std::ifstream in("data.dat", std::ios::in);

	//Считываем данные из файла, если такие есть
	if (in) {
		
		std::size_t posCount = 0;
		in.read(reinterpret_cast<char*>(&posCount), sizeof(posCount));
		in.read(reinterpret_cast<char*>(&Position::count), sizeof(Position::count));

		for (auto i = 0U; i < posCount; i++) {
			std::string _name;
			unsigned int _id;
			srlz::read(in, _name);
			in.read(reinterpret_cast<char*>(&_id), sizeof(_id));
			
			//Проверяем входящий id на уникальность
			bool isDuplicate = std::count_if(allPos.begin(), allPos.end(), [_id](auto pos) {

				auto state = pos->getId() == _id;
				term::clrscr();

				return state;
			});
			
			if (isDuplicate) {
				std::cout << "File 'data.dat' is corrupted" << std::endl
						<< "1 - Clear list and continue"  	<< std::endl
						<< "2 - Exit "						<< std::endl;

				switch (term::getch()) {
					case 49: {

						in.close();
						std::fstream of("data.dat", std::ios::trunc);
						of.write("",0);
						of.close();
						allPos.clear();
						break;
					}

					case 50: {
						return 0;
					}
					
					default: {
						term::clrscr();
						std::cout << "Invalid key.";
						break;
					}
				}
				break;	
			}
			allPos.push_back(new Position(_name, _id));
		}
	}
	

	while (true) {

		term::clrscr();
		std::cout   << "___________Menu___________" << std::endl
					<< "1. Add new position" << std::endl
					<< "2. Print position's list" << std::endl
					<< "3. Find positions by name" << std::endl
					<< "4. Delete position by id" << std::endl
					<< "5. Exit" << std::endl;

		switch (term::getch()) {

			case 49 : { //1
				term::clrscr();
				allPos.push_back(new Position); // delete on p.5
				break;
			}

			case 50: {//2

				term::clrscr();
				if (auto posCount = allPos.size())
					Position::print(allPos);
				else
					std::cout << "List is empty." << std::endl;

				std::cout << "Press any key." << std::endl;
				term::getch();
				break;
			}

			case 51: {//3
				term::clrscr();
				Position::displayByName(allPos);
				
				std::cout << std::endl
				  		  << "Press any key." << std::endl;
				term::getch();
				break;
			}

			case 52 : {//4
				term::clrscr();

				if (allPos.size()) {

					unsigned int _id;
					std::cout << "Enter id of deleting element: " << std::endl;
					std::cin >> _id;

					auto newEnd = std::remove_if(allPos.begin(), allPos.end(), [_id](auto pos) {

						auto state = pos->getId() == _id;
						term::clrscr();
						std::cout << (state ? "Position has removed" : "Position not found.") << std::endl;

						return state;
					});
					allPos.erase(newEnd, allPos.end());
				} else
					std::cout << "List is empty." << std::endl;

					std::cout << "Press any key." << std::endl;
					term::getch();

				break;
			}

			case 53: {//5
			
			//Записываем изменения в файл
			std::ofstream out("data.dat", std::ios::binary);
			std::size_t posCount = allPos.size();
			out.write(reinterpret_cast<char*>(&posCount), sizeof(posCount));
			out.write(reinterpret_cast<char*>(&Position::count), sizeof(Position::count));
			for (auto i = 0U; i < posCount; i++) {
				auto _id = allPos[i]->getId();
				auto _name = allPos[i]->getName();
				srlz::write(out, _name);
				out.write(reinterpret_cast<char*>(&_id), sizeof(_id));
			}
	
				allPos.clear();
				return 0;
			}

			default: {
				term::clrscr();
				std::cout << "Invalid key.";
				break;
			}
		}
	}

	return 0;
}


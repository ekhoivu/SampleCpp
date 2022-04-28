// Khoi Vu
// 124611203
// kvu8@myseneca.ca
// April 5th, 2022

//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_MENU_H
#define SDDS_MENU_H

#define _CRT_SECURE_NO_WARNINGS

namespace sdds {

	const int MAX_MENU_OPTIONS = 15;

	class Menu {
		char* m_menuContext;
		unsigned int m_numberOptions;
	public:
		//Contrustor
		Menu(const char* menuContext = nullptr, int numberOptions = 0);
		//Rule of three
		~Menu();
		//operators
		Menu& operator=(const char* des);
		Menu& operator=(const unsigned int val);
		//method
		unsigned int run() const;
	};

}

#endif
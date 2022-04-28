// Khoi Vu
// 124611203
// kvu8@myseneca.ca
// March 15th, 2022

//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "Menu.h"
#include "Utils.h"
#include <cstring>
#include <iostream>

using namespace std;
using namespace sdds;

namespace sdds {
	Menu::Menu(const char* menuContext, int numberOptions) {
		m_menuContext = nullptr;
		m_numberOptions = 0;
		if ((numberOptions > 0 && numberOptions <= MAX_MENU_OPTIONS) && (menuContext != nullptr)) {
			m_menuContext = new char[strlen(menuContext) + 1];
			strcpy(m_menuContext, menuContext);
			m_numberOptions = numberOptions;
		}
	}
	Menu::~Menu() {
		delete[] m_menuContext;
		m_menuContext = nullptr;
	}
	Menu& Menu::operator=(const char* des) {
		if (des != nullptr) {
			delete[] m_menuContext;
			m_menuContext = new char[strlen(des) + 1];
			strcpy(m_menuContext, des);
		}
		return *this;
	}
	Menu& Menu::operator=(const unsigned int val) {
		m_numberOptions = val;
		return *this;
	}
	unsigned int Menu::run() const {
		unsigned int input;
		bool flag = false; bool done = false;
		cout << m_menuContext << "0- Exit" << endl;
		cout << "> ";
		cin >> input;
		do {
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid Integer, retry: ";
				cin >> input;
			}
			else {
				done = true;
			}
		} while (!done);
		done = false;
		do {
			if (input > m_numberOptions) {
				cout << "Value out of range [0<=val<=" << m_numberOptions << "]: ";
				cin >> input;
				do {
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1000, '\n');
						cout << "Invalid Integer, retry: ";
						cin >> input;
					}
					else {
						done = true;
					}
				} while (!done);
			}
			else {
				flag = true;
			}
		} while (!flag);
		return input;
	}
}
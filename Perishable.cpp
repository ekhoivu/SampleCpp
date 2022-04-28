#define _CRT_SECURE_NO_WARNINGS

#include "Perishable.h"
#include "Utils.h"
#include <cstring>
#include <fstream>
#include <iomanip>

namespace sdds {
	Perishable::Perishable() {
		m_instructions = nullptr;
	}
	Perishable::Perishable(const Perishable& perishable) :Perishable() {
		if (perishable.m_instructions != nullptr) {
			*this = perishable;
			Item::operator=(perishable);
		}
		else {
			m_instructions = nullptr;
		}
	}
	Perishable& Perishable::operator=(const Perishable& perishable) {
		if (this != &perishable) {
			delete[] m_instructions;
			m_expiry = perishable.m_expiry;
			m_instructions = new char[strlen(perishable.m_instructions) + 1];
			strcpy(m_instructions, perishable.m_instructions);
			Item::operator=(perishable);
		}
		return *this;
	}
	Perishable::~Perishable() {
		delete[] m_instructions;
		m_instructions = nullptr;
	}
	const Date& Perishable::expiry() {
		return m_expiry;
	}
	int Perishable::readSku(istream& istr) {
		int input;
		cout << "SKU: ";
		input = ut.getInt(10000, 39999);
		m_sku = input;
		return input;
	}
	ofstream& Perishable::save(ofstream& ofstr)const {
		Date d;
		d = m_expiry;
		d.formatted(false);
		if (m_state.operator bool()) {
			Item::save(ofstr);
			ofstr << '\t';
			if (m_instructions != nullptr && m_instructions[0] != '\0') {
				ofstr << m_instructions;
			}
			ofstr << '\t';
			ofstr << d;
		}
		return ofstr;
	}
	ifstream& Perishable::load(ifstream& ifstr) {
		char temp[401];
		char next;
			delete[] m_instructions;
		m_instructions = nullptr;
		Item::load(ifstr);
		ifstr.ignore();
		next = ifstr.peek();
		if (next == '\t') {
			ifstr.ignore();
			temp[0] = '\0';
			m_instructions = new char[strlen(temp) + 1];
			strcpy(m_instructions, temp);
		}
		else {
			ifstr.get(temp, 400, '\t');
			m_instructions = new char[strlen(temp) + 1];
			strcpy(m_instructions, temp);
		}
		if (temp[0] == '\0') {
			ifstr >> m_expiry;
		}
		else {
			ifstr >> m_expiry;
		}
		ifstr.ignore(1000, '\n');
		if (ifstr.fail()) {
			m_state.operator=("Input file stream read (perishable) failed!");
		}
		return ifstr;
	}
	ostream& Perishable::display(ostream& ostr)const {
		if (!m_state.operator bool()) {
			ostr << m_state;
		}
		else {
			if (linear()) {
				Item::display(ostr);
				if (m_instructions != nullptr && m_instructions[0] != '\0') {
					ostr << '*';
				}
				else {
					ostr << " ";
				}
				ostr << m_expiry;
			}
			else {
				ostr << "Perishable ";
				Item::display(ostr);
				ostr << "Expiry date: " << m_expiry << endl;;
				if (m_instructions != nullptr && m_instructions[0] != '\0') {
					ostr << "Handling Instructions: " << m_instructions << endl;
				}
			}
		}
		return ostr;
	}
	istream& Perishable::read(istream& istr) {
		char next;
		char temp[401];
		Item::read(istr);
		cout << "Expiry date (YYMMDD): ";
		istr >> m_expiry;
		istr.clear();
		istr.ignore(1000, '\n');
		cout << "Handling Instructions, ENTER to skip: ";
		next = istr.peek();
		if (next != '\n') {
			istr.get(temp, 400, '\n');
			delete[] m_instructions;
			m_instructions = new char[strlen(temp) + 1];
			strcpy(m_instructions, temp);
		}
		istr.clear();
		istr.ignore(1000, '\n');
		if (istr.fail()) {
			m_state.operator=("Perishable console date entry failed!");
		}
		return istr;
	}
	Perishable::operator bool() const {
		return (m_sku != 0 && m_state.operator bool());
	}
}
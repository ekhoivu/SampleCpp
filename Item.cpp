// Khoi Vu
// 124611203
// kvu8@myseneca.ca
// March 28th, 2022

//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#define _CRT_SECURE_NO_WARNINGS

#include <iomanip>
#include <cstring>
#include <fstream>
#include "Item.h"
#include "Utils.h"
#include "Perishable.h"

namespace sdds {
	bool Item::linear() const {
		return m_linear;
	}
	Item::Item() {
		m_price = 0;
		m_qty = 0;
		m_qtyNeeded = 0;
		m_sku = 0;
		m_description = nullptr;
		m_linear = false;
	}
	Item::Item(const Item& item):Item() {
		if (item.m_description != nullptr && item.m_description[0] != '\0') {
			*this = item;
		}
	}
	Item& Item::operator=(const Item& item) {
		if (this != &item) {
			m_price = item.m_price;
			m_qty = item.m_qty;
			m_qtyNeeded = item.m_qtyNeeded;
			delete[] m_description;
			m_description = new char[strlen(item.m_description) + 1];
			strcpy(m_description, item.m_description);
			m_linear = item.m_linear;
			m_sku = item.m_sku;
		}
		return *this;
	}
	Item::~Item() {
		delete[] m_description;
		m_description = nullptr;
	}
	int Item::qtyNeeded() const {
		return m_qtyNeeded;
	}
	int Item::qty() const {
		return m_qty;
	}
	Item::operator double() const {
		return m_price;
	}
	Item:: operator bool() const {
		return (m_state.operator bool());
	}
	int Item::operator-=(int value) {
		m_qty -= value;
		return m_qty;
	}
	int Item::operator+=(int value) {
		m_qty += value;
		return m_qty;
	}
	void Item::linear(bool isLinear) {
		m_linear = isLinear;
	}
	Item& Item::clear() {
		m_state.clear();
		return *this;
	}
	bool Item::operator==(int sku)const {
		return (m_sku == sku);
	}
	bool Item::operator==(const char* description)const {
		bool returnValue = true;
		if ((m_description == nullptr) || (description == nullptr) || (ut.strStr(m_description, description) == 0)) {
			returnValue = false;
		}
		return returnValue;
	}
	ofstream& Item::save(ofstream& ofstr)const {
		if (m_state.operator bool()) {
			ofstr << m_sku << '\t' << m_description << '\t' << m_qty << '\t' << m_qtyNeeded << '\t';
			ofstr << fixed << setprecision(2) << m_price;
		}
		return ofstr;
	}
	ifstream& Item::load(ifstream& ifstr) {
		char temp[401];
		delete[] m_description;
		ifstr >> m_sku;
		ifstr.ignore();
		ifstr.get(temp, 400, '\t');
		m_description = new char[strlen(temp) + 1];
		strcpy(m_description, temp);
		ifstr.ignore();
		ifstr >> m_qty;
		ifstr.ignore();
		ifstr >> m_qtyNeeded;
		ifstr.ignore();
		ifstr >> m_price;
		if (ifstr.fail()) {
			m_state.operator=("Input file stream read failed!");
		}
		return ifstr;
	}
	ostream& Item::display(ostream& ostr)const {
		char description[36];
		if (!m_state.operator bool()) {
			ostr << m_state;
		}
		else {
			if (m_linear) {
				ostr << " ";
				ostr << setw(5);
				ostr << m_sku << " | ";
				ostr << setw(35);
				ostr << left;
				ostr << setfill(' ');
				if (strlen(m_description) > 35) {
					strncpy(description, m_description, 35);
					description[35] = '\0';
					ostr << description << " | ";
				}
				else {
					ostr << m_description << " | ";
				}
				ostr << right;
				ostr << setw(4);
				ostr << m_qty << " | ";
				ostr << setw(4);
				ostr << m_qtyNeeded << " | ";
				ostr << setw(7);
				ostr << m_price << " |";
			}
			else {
				ostr << "AMA Item:" << endl;
				ostr << m_sku << ": " << m_description << endl;
				ostr << "Quantity Needed: " << m_qtyNeeded << endl;
				ostr << "Quantity Available: " << m_qty << endl;
				ostr << "Unit Price: $" << m_price << endl;
				ostr << "Needed Purchase Fund: $";
				ostr << fixed << setprecision(2) << (m_qtyNeeded - m_qty) * m_price << endl;
			}
		}
		return ostr;
	}
	int Item::readSku(istream& istr) {
		int input;
		cout << "SKU: ";
		input = ut.getInt(40000, 99999);
		m_sku = input;
		return input;
	}
	istream& Item::read(istream& istr) {
		char description[201];
		delete[] m_description;
		m_state.clear();
		cout << "AMA Item:" << endl;
		cout << "SKU: " << m_sku << endl;
		cout << "Description: ";
		istr.clear();
		istr.ignore(1000, '\n');
		istr.get(description, 200, '\n');
		m_description = new char[strlen(description) + 1];
		strcpy(m_description, description);
		istr.clear();
		istr.ignore(1000,'\n');
		cout << "Quantity Needed: ";
		m_qtyNeeded = ut.getInt(1, 9999);
		cout << "Quantity On Hand: ";
		m_qty = ut.getInt(0, m_qtyNeeded);
		cout << "Unit Price: $";
		m_price = ut.getDouble(0, 9999);
		if (!istr) {
			m_state.operator=("Console entry failed!");
		}
		return istr;
	}
}
// Khoi Vu
// 124611203
// kvu8@myseneca.ca
// April 5th, 2022

//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H

#include "Date.h"
#include "Item.h"

namespace sdds {
	class Perishable : public Item {
		Date m_expiry;
		char* m_instructions;
	public:
		Perishable();
		//Rule of three
		Perishable(const Perishable& perishable);
		Perishable& operator=(const Perishable& perishable);
		~Perishable();
		const Date& expiry();
		int readSku(istream& istr);
		ofstream& save(ofstream& ofstr)const;
		ifstream& load(ifstream& ifstr);
		ostream& display(ostream& ostr)const;
		istream& read(istream& istr);
		operator bool() const;
	};
}

#endif
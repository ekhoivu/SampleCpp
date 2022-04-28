// Khoi Vu
// 124611203
// kvu8@myseneca.ca
// April 5th, 2022

//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

#include "iProduct.h"
#include "Status.h"

namespace sdds {
	class Item : public iProduct {
		double m_price;
		int m_qty;
		int m_qtyNeeded;
		char* m_description;
		bool m_linear;
	protected:
		Status m_state;
		int m_sku;
		bool linear() const;
	public:
		Item();
		//Rule of three
		Item(const Item& item);
		Item& operator=(const Item& item);
		~Item();
		int qtyNeeded() const;
		int qty() const;
		operator double() const;
		operator bool() const;
		int operator-=(int value);
		int operator+=(int value);
		void linear(bool isLinear);
		Item& clear();
		bool operator==(int sku)const;
		bool operator==(const char* description)const;
		ofstream& save(ofstream& ofstr)const;
		ifstream& load(ifstream& ifstr);
		ostream& display(ostream& ostr)const;
		int readSku(istream& istr);
		istream& read(istream& istr);
	};
}

#endif
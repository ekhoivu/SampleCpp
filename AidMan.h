// Khoi Vu
// 124611203
// kvu8@myseneca.ca
// April 5th, 2022

//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H

#include "Menu.h"
#include "iProduct.h"

namespace sdds {
	const int sdds_max_num_items = 100;
	class AidMan {
		char* m_fileName;
		Menu m_menu;
		unsigned int menu() const;
		iProduct* iproduct[sdds_max_num_items];
		int m_numProduct;
	public:
		//Constructor
		AidMan();
		//Rule of three
		~AidMan();
		void run();
		void save();
		void deallocate();
		bool load();
		int list(const char* sub_desc = nullptr);
		int search(int sku) const;
		void listItem();
		void addItem();
		void remove(int index);
		void removeItem();
		void updateQuantity();
		void sortItem();
		void shipItem();
	};
}

#endif
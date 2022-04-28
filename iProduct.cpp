// Khoi Vu
// 124611203
// kvu8@myseneca.ca
// March 28th, 2022

//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "iProduct.h"

namespace sdds {
	iProduct::~iProduct() {
		// do nothing
	}
	ostream& operator<<(ostream& ostr, const iProduct& iproduct) {
		iproduct.display(ostr);
		return ostr;
	}
	istream& operator>>(istream& istr, iProduct& iproduct) {
		iproduct.read(istr);
		return istr;
	}
}
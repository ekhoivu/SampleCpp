// Khoi Vu
// 124611203
// kvu8@myseneca.ca
// April 5th, 2022

//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H

#include <iostream>

using namespace std;

namespace sdds {
	class Status {
		char* m_desStaObj;
		int m_statusCode;
		void setEmpty();
	public:
		//Constructors
		Status();
		Status(const char* des);
		//Rule of three
		Status(const Status& status);
		Status& operator=(const Status& status);
		~Status();
		//Conversion Overloads
		Status& operator=(const int val);
		Status& operator=(const char* des);
		//Type Conversions Overloads
		operator int() const;
		operator const char* () const;
		operator bool() const;
		Status& clear();
	};
	ostream& operator<<(ostream& ostr, const Status& status);

}

#endif // !SDDS_STATUS_H


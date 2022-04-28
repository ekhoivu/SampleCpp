// Khoi Vu
// 124611203
// kvu8@myseneca.ca
// April 5th, 2022

//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.


#ifndef SDDS_DATE_H
#define SDDS_DATE_H

#define _CRT_SECURE_NO_WARNINGS
#include "Status.h"

#include <iostream>
using namespace sdds;

namespace sdds {

	const int MaxYearValue = 2030;

	class Date {
		int m_year;
		int m_month;
		int m_day;
		Status m_state;
		bool m_formatted;
		bool validate();
		int uniqueDateValue() const;
		void set(int year, int month, int day);
	public:
		//Contructors
		Date();
		Date(const int year, const int month, const int day);
		//Comparision Overloads
		bool operator==(const Date& date);
		bool operator!=(const Date& date);
		bool operator<(const Date& date);
		bool operator>(const Date& date);
		bool operator<=(const Date& date);
		bool operator>=(const Date& date);
		const Status& state();
		Date& formatted(bool value);
		operator bool() const;
		ostream& write(ostream& ostr) const;
		istream& read(istream& istr);
	};
	ostream& operator<<(ostream& ostr, const Date& date);
	istream& operator>>(istream& istr, Date& date);

}

#endif // !SDDS_DATE_H
// Khoi Vu
// 124611203
// kvu8@myseneca.ca
// March 15th, 2022

//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#define _CRT_SECURE_NO_WARNINGS

#include <ctime>
#include <iostream>
#include <iomanip>
#include <math.h>
#include "Date.h"
#include "Utils.h"

using namespace std;
using namespace sdds;

namespace sdds {
	void Date::set(int year, int month, int day) {
		m_year = year;
		m_month = month;
		m_day = day;
	}
	bool Date::validate() {
		int currentYear = 0;
		int currentMonth = 0;
		int currentDay = 0;
		ut.getSystemDate(&currentYear, &currentMonth, &currentDay);
		bool flag = true;
		char invalidYear[] = "Invalid year in date";
		char invalidMonth[] = "Invalid month in date";
		char invalidDay[] = "Invalid day in date";
		char invalidDate[] = "Invalid date value";
		int numDaysInMonth = 0;
		numDaysInMonth = ut.daysOfMon(m_month, m_year);
		if (m_day == 0) {
			m_state.operator=(invalidDate);
			m_state.operator=(0);
			flag = false;
		}
		else {
			if (m_year < currentYear || m_year > MaxYearValue) {
				m_state.operator=(invalidYear);
				m_state.operator=(1);
				flag = false;
			}
			else {
				if (m_month < 1 || m_month > 12) {
					m_state.operator=(invalidMonth);
					m_state.operator=(2);
					flag = false;
				}
				else {
					if (m_day < 1 || m_day > numDaysInMonth) {
						m_state.operator=(invalidDay);
						m_state.operator=(3);
						flag = false;
					}
				}
			}
		}
		if (flag) {
			m_state.clear();
		}
		return flag;
	}
	int Date::uniqueDateValue() const {
		return (m_year * 372 + m_month * 31 + m_day);
	}
	Date::Date() {
		ut.getSystemDate(&m_year, &m_month, &m_day);
		m_formatted = 1;
	}
	Date::Date(const int year, const int month, const int day) {
		m_year = year;
		m_month = month;
		m_day = day;
		m_formatted = 1;
	}
	bool Date::operator==(const Date& date) {
		return (this->uniqueDateValue() == date.uniqueDateValue());
	}
	bool Date::operator!=(const Date& date) {
		return (this->uniqueDateValue() != date.uniqueDateValue());
	}
	bool Date::operator<(const Date& date) {
		return (this->uniqueDateValue() < date.uniqueDateValue());
	}
	bool Date::operator>(const Date& date) {
		return (this->uniqueDateValue() > date.uniqueDateValue());
	}
	bool Date::operator<=(const Date& date) {
		return (this->uniqueDateValue() <= date.uniqueDateValue());
	}
	bool Date::operator>=(const Date& date) {
		return (this->uniqueDateValue() >= date.uniqueDateValue());
	}
	const Status& Date::state() {
		return m_state;
	}
	Date& Date::formatted(bool value) {
		if (value)
			m_formatted = true;
		else
			m_formatted = false;
		return *this;
	}
	Date::operator bool() const {
		return m_state;
	}
	ostream& Date::write(ostream& ostr) const {
		if (m_formatted) {
			ostr << m_year << "/";
			ostr << setw(2) << setfill('0') << m_month << "/" << m_day;
		}
		else {
			ostr << m_year - 2000;
			ostr << setw(2) << setfill('0') << m_month << m_day;
		}
		return ostr;
	}
	istream& Date::read(istream& istr) {
		int currentYear = 0;
		int currentMonth = 0;
		int currentDay = 0;
		ut.getSystemDate(&currentYear, &currentMonth, &currentDay);
		bool flag = true;
		int tempVal = 0;
		int tempYear = 0;
		int tempMonth = 0;
		int tempDay = 0;
		istr >> tempVal;
		if (tempVal < 99) {
			tempYear = currentYear;
			tempMonth = 0;
			tempDay = tempVal;
		}
		else if (tempVal > 99 && tempVal < 9999) {
			tempYear = currentYear;
			tempMonth = floor(tempVal / 100);
			tempDay = tempVal - (tempMonth * 100);
		}
		else {
			tempYear = floor(tempVal / 10000) + 2000;
			tempMonth = floor((tempVal - ((tempYear - 2000) * 10000)) / 100);
			tempDay = tempVal - ((tempYear - 2000) * 10000 + (tempMonth * 100));
		}
		set(tempYear, tempMonth, tempDay);
		flag = this->validate();
		if (!flag) {
			istr.setstate(ios::badbit);
		}
		return istr;
	}
	ostream& operator<<(ostream& ostr, const Date& date) {
		date.write(ostr);
		return ostr;
	}
	istream& operator>>(istream& istr, Date& date) {
		date.read(istr);
		return istr;
	}
}
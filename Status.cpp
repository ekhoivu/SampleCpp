// Khoi Vu
// 124611203
// kvu8@myseneca.ca
// March 15th, 2022

//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include "Status.h"
#include "Utils.h"

using namespace std;
using namespace sdds;

namespace sdds {
	void Status::setEmpty() {
		m_desStaObj = nullptr;
		m_statusCode = 0;
	}
	Status::Status() {
		setEmpty();
	}
	Status::Status(const char* des) :Status() {
		setEmpty();
		m_desStaObj = new char[strlen(des) + 1];
		strcpy(m_desStaObj, des);
	}
	Status::Status(const Status& status) : Status() {
		*this = status;
	}
	Status& Status::operator=(const Status& status) {
		if (this != &status && (status.m_desStaObj != nullptr)) {
			delete[] m_desStaObj;
			m_desStaObj = new char[strlen(status.m_desStaObj) + 1];
			strcpy(m_desStaObj, status.m_desStaObj);
			m_statusCode = status.m_statusCode;
		}
		else {
			setEmpty();
		}
		return *this;
	}
	Status::~Status() {
		delete[] m_desStaObj;
		setEmpty();
	}
	Status& Status::operator=(const int val) {
		if (val) {
			m_statusCode = val;
		}
		return *this;
	}
	Status& Status::operator=(const char* des) {
		if (des != nullptr && des[0] != '\0') {
			delete[] m_desStaObj;
			m_desStaObj = new char[strlen(des) + 1];
			strcpy(m_desStaObj, des);
		}
		return *this;
	}
	Status::operator int() const {
		return m_statusCode;
	}
	Status::operator const char* () const {
		return m_desStaObj;
	}
	Status::operator bool() const {
		return (m_desStaObj == nullptr);
	}
	Status& Status::clear() {
		delete[] m_desStaObj;
		setEmpty();
		m_statusCode = 0;
		return *this;
	}
	ostream& operator<<(ostream& ostr, const Status& status) {
		if (!status.operator bool()) {
			if (status.operator int() != 0) {
				ostr << "ERR#" << status.operator int() << ": ";
			}
			ostr << status.operator const char* ();
		}
		return ostr;
	}
}
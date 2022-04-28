#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include "Utils.h"
#include <cstring>
#include <iomanip>
using namespace std;
namespace sdds {
	Utils ut;
	void Utils::testMode(bool testmode) {
		m_testMode = testmode;
	}
	void Utils::getSystemDate(int* year, int* mon, int* day) {
		if (m_testMode) {
			if (day) *day = sdds_testDay;
			if (mon) *mon = sdds_testMon;
			if (year) *year = sdds_testYear;
		}
		else {
			time_t t = std::time(NULL);
			tm lt = *localtime(&t);
			if (day) *day = lt.tm_mday;
			if (mon) *mon = lt.tm_mon + 1;
			if (year) *year = lt.tm_year + 1900;
		}
	}
	int Utils::daysOfMon(int month, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = (month >= 1 && month <= 12 ? month : 13) - 1;
		return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}
	int Utils::getInt(int min, int max) {
		int input;
		bool done = 0;
		cin >> input;
		do {
			if (!input) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid Integer, retry: ";
				cin >> input;
			}
		} while (!input);
		do {
			if (input < min || input > max) {
				cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
				cin >> input;
				do {
					if (!input) {
						cin.clear();
						cin.ignore(1000, '\n');
						cout << "Invalid Integer, retry: ";
						cin >> input;
					}
				} while (!input);
			}
			else {
				done = 1;
			}
		} while (!done);
		return input;
	}
	double Utils::getDouble(double min, double max) {
		double input;
		bool done = 0;
		cin >> input;
		do {
			if (!input) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid number, retry: ";
				cin >> input;
			}
		} while (!input);
		do {
			if (input < min || input > max) {
				cout << fixed << setprecision(2);
				cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
				cin >> input;
				do {
					if (!input) {
						cin.clear();
						cin.ignore(1000, '\n');
						cout << "Invalid number, retry: ";
						cin >> input;
					}
				} while (!input);
			}
			else {
				done = 1;
			}
		} while (!done);
		return input;
	}
	int Utils::strnCmp(const char* s1, const char* s2, int len) {
		int i = 0;
		while (i < len - 1 && s1[i] && s2[i] && s1[i] == s2[i]) {
			i++;
		}
		return s1[i] - s2[i];
	}
	int Utils::strLen(const char* str) {
		int len;
		for (len = 0; str[len]; len++);
		return len;
	}
	const char* Utils::strStr(const char* str, const char* find) {
		const char* faddress = nullptr;
		int i, flen = strLen(find), slen = strLen(str);
		for (i = 0; i <= slen - flen && strnCmp(&str[i], find, flen); i++);
		if (i <= slen - flen) faddress = &str[i];
		return faddress;
	}
	int Utils::getIntEnter(int min, int max) {
		char input;
		int digit;
		bool done = 0;
		cin.clear();
		cin.ignore(1000, '\n');
		input = cin.get();
		if (input == '\n') {
			input = 0;
		}
		else {
			do {
				digit = input - '0';
				if (!digit) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid Integer, retry: ";
					cin >> input;
				}
			} while (!digit);
			do {
				if (digit < min || digit > max) {
					cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
					cin >> digit;
					do {
						if (!digit) {
							cin.clear();
							cin.ignore(1000, '\n');
							cout << "Invalid Integer, retry: ";
							cin >> digit;
						}
					} while (!digit);
				}
				else {
					done = 1;
				}
			} while (!done);
			input = digit;
		}
		return input;
	}
	int Utils::getIntZero(int max) {
		int input;
		bool done = 0;
		cin >> input;
		if (input == 0) {
			// do nothing
		}
		else {
			do {
				if (!input) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid Integer, retry: ";
					cin >> input;
				}
			} while (!input);
			do {
				if (input > max) {
					cout << "Value out of range [0" << "<=val<=" << max << "]: ";
					cin >> input;
					do {
						if (!input) {
							cin.clear();
							cin.ignore(1000, '\n');
							cout << "Invalid Integer, retry: ";
							cin >> input;
						}
					} while (!input);
				}
				else {
					done = 1;
				}
			} while (!done);
		}
		return input;
	}
}
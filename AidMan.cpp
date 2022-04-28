// Khoi Vu
// 124611203
// kvu8@myseneca.ca
// March 15th, 2022

//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "AidMan.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "iProduct.h"
#include "Item.h"
#include "Perishable.h"

using namespace std;
using namespace sdds;

namespace sdds {
	AidMan::AidMan() {
		int i;
		m_fileName = nullptr;
		m_menu.operator=("1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n");
		m_menu.operator=(7);
		for (i = 0; i < sdds_max_num_items; i++) {
			iproduct[i] = nullptr;
		}
		m_numProduct = 0;
	}
	AidMan::~AidMan() {
		delete[] m_fileName;
		m_fileName = nullptr;
	}
	unsigned int AidMan::menu() const {
		int year, month, day, input;
		ut.getSystemDate(&year, &month, &day);
		cout << "Aid Management System" << endl;
		cout << "Date: " << year << "/";
		cout << setw(2) << setfill('0') << month << "/" << day << endl;
		if (m_fileName == nullptr) {
			cout << "Data file: No file" << endl;
		}
		else {
			cout << "Data file: " << m_fileName << endl;
		}
		cout << "---------------------------------" << endl;
		input = m_menu.run();
		return input;
	}
	void AidMan::run() {
		int menuSelection;
		bool done = false;
		do {
			menuSelection = menu();
			if (m_fileName == nullptr && menuSelection != 0) {
				menuSelection = 7;
			}
			switch (menuSelection) {
			case 0:
				done = true;
				cout << "Exiting Program!" << endl;
				break;
			case 1:
				cout << endl;
				cout << "****List Items****" << endl;
				listItem();
				cout << endl;
				break;
			case 2:
				cout << endl;
				cout << "****Add Item****" << endl;
				addItem();
				cout << endl;
				break;
			case 3:
				cout << endl;
				cout << "****Remove Item****" << endl;
				removeItem();
				cout << endl;
				break;
			case 4:
				cout << endl;
				cout << "****Update Quantity****" << endl;
				updateQuantity();
				cout << endl;
				break;
			case 5:
				cout << endl;
				cout << "****Sort****" << endl;
				sortItem();
				cout << endl;
				break;
			case 6:
				cout << endl;
				cout << "****Ship Items****" << endl;
				shipItem();
				cout << endl;
				break;
			case 7:
				cout << endl;
				cout << "****New/Open Aid Database****" << endl;
				load();
				cout << endl;
				break;
			default:
				break;
			}
		} while (!done);
		save();
		deallocate();
	}
	void AidMan::save() {
		int i;
		if (m_fileName != nullptr) {
			ofstream file(m_fileName);
			for (i = 0; i < m_numProduct; i++) {
				iproduct[i]->save(file);
				file << endl;
			}
		}
	}
	void AidMan::deallocate() {
		int i;
		for (i = 0; i < m_numProduct; i++) {
			if (iproduct[i] != nullptr) {
				delete iproduct[i];
			}
		}
	}
	bool AidMan::load() {
		int input, firstDigit;
		char next;
		char filename[101];
		save();
		deallocate();
		if (m_fileName == nullptr) {
			cout << "Enter file name: ";
			cin >> filename;
			m_fileName = new char[strlen(filename) + 1];
			strcpy(m_fileName, filename);
		}
		ifstream file(m_fileName);
		if (!file) {
			cout << "Failed to open \"" << m_fileName << "\" for reading!\n";
			cout << "Would you like to create a new data file?";
			cout << "\n1- Yes!\n0 - Exit\n>";
			input = ut.getInt(0, 1);
			switch (input) {
			case 1:
				file.open(m_fileName);
				break;
			default:
				break;
			}
		}
		else {
			do {
				next = file.peek();
				firstDigit = next - '0';
				if (!firstDigit || firstDigit < 0) {
					file.setstate(ios::badbit);
				}
				else {
					if (firstDigit > 0 && firstDigit < 4) {
						iproduct[m_numProduct] = new Perishable;
						iproduct[m_numProduct]->load(file);
						if (!iproduct[m_numProduct]->operator bool()) {
							delete iproduct[m_numProduct];
						}
						else {
							m_numProduct++;
						}
					}
					else {
						iproduct[m_numProduct] = new Item;
						iproduct[m_numProduct]->load(file);
						file.ignore();
						if (!iproduct[m_numProduct]->operator bool()) {
							delete iproduct[m_numProduct];
						}
						else {
							m_numProduct++;
						}
					}
				}
			} while (!file.fail());
		}
		cout << m_numProduct << " records loaded!" << endl;
		return (m_numProduct != 0);
	}
	int AidMan::list(const char* sub_desc) {
		int i, counter;
		counter = 0;
		if (sub_desc == nullptr) {
			cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
			for (i = 0; i < m_numProduct; i++) {
				cout << setw(4) << setfill(' ');
				cout << i + 1 << " |";
				iproduct[i]->linear(true);
				cout << *iproduct[i];
				counter++;
				cout << endl;
			}
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		}
		else {
			cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
			for (i = 0; i < m_numProduct; i++) {
				if (iproduct[i]->operator==(sub_desc)) {
					iproduct[i]->linear(true);
					cout << setw(4) << setfill(' ');
					cout << i + 1 << " |" << *iproduct[i];
					counter++;
					cout << endl;
				}
			}
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		}
		return (counter);
	}
	int AidMan::search(int sku) const {
		int i, foundIndex;
		bool found = false;
		foundIndex = 0;
		for (i = 0; i < sdds_max_num_items; i++) {
			if (iproduct[i]->operator==(sku)) {
				foundIndex = i;
				found = true;
			}
		}
		if (!found) {
			foundIndex = -1;
		}
		return foundIndex;
	}
	void AidMan::listItem() {
		int record, input;
		record = list();
		if (record == 0) {
			cout << "The list is emtpy!" << endl;
		}
		else {
			cout << "Enter row number to display details or <ENTER> to continue:\n> ";
			input = ut.getIntEnter(0, m_numProduct);
			if (input == 0) {
				// do nothing;
			}
			else {
				iproduct[(input - 1)]->linear(false);
				cout << *iproduct[input - 1];
			}
		}
	}
	void AidMan::addItem() {
		int typeInput;
		bool foundExisting = false;
		int inputSKU;
		int i;
		if (m_numProduct == sdds_max_num_items) {
			cout << "Database full!";
		}
		else {
			cout << "1- Perishable\n2- Non-Perishable\n-----------------\n0- Exit\n> ";
			typeInput = ut.getIntZero(2);
			switch (typeInput) {
			case 0:
				cout << "Aborted\n";
				break;
			case 1:
				iproduct[m_numProduct] = new Perishable;
				inputSKU = iproduct[m_numProduct]->readSku(cin);
				for (i = 0; i < (m_numProduct - 1); i++) {
					if (iproduct[i]->operator==(inputSKU)) {
						foundExisting = true;
					}
				}
				if (foundExisting) {
					cout << "Sku: " << inputSKU << "is already in the system, try updating quantity instead.\n";
					delete iproduct[m_numProduct];
				}
				else {
					cin >> *iproduct[m_numProduct];
					m_numProduct++;
				}
				break;
			case 2:
				iproduct[m_numProduct] = new Item;
				inputSKU = iproduct[m_numProduct]->readSku(cin);
				for (i = 0; i < (m_numProduct - 1); i++) {
					if (iproduct[i]->operator==(inputSKU)) {
						foundExisting = true;
					}
				}
				if (foundExisting) {
					cout << "Sku: " << inputSKU << " is already in the system, try updating quantity instead.\n";
					delete iproduct[m_numProduct];
				}
				else {
					cin >> *iproduct[m_numProduct];
					m_numProduct++;
				}
				break;
			default:
				break;
			}
		}
	}
	void AidMan::remove(int index) {
		int i;
		delete iproduct[index];
		for (i = index; i < m_numProduct; i++) {
			iproduct[i] = iproduct[i + 1];
		}
		delete iproduct[i + 1];
		m_numProduct--;
	}
	void AidMan::removeItem() {
		char des[101];
		int found, foundIndex, inputSKU, i, confirmation;
		bool foundExisting = false;
		cout << "Item description: ";
		cin >> des;
		found = list(des);
		if (!found) {
			cout << "No matches found!\n";
		}
		else {
			cout << "Enter SKU: ";
			cin >> inputSKU;
			for (i = 0; i < (m_numProduct - 1) && !foundExisting; i++) {
				if (iproduct[i]->operator==(inputSKU)) {
					foundExisting = true;
					foundIndex = i;
				}
			}
			if (!foundExisting) {
				cout << "SKU not found!";
			}
			else {
				iproduct[foundIndex]->linear(false);
				cout << "Following item will be removed: \n";
				cout << *iproduct[foundIndex];
				cout << "\nAre you sure?\n1- Yes!\n0- Exit\n> ";
				confirmation = ut.getIntZero(1);
				switch (confirmation) {
				case 0:
					cout << "Aborted!\n";
					break;
				case 1:
					remove(foundIndex);
					cout << "Item removed!\n";
					break;
				default:
					break;
				}
			}
		}
	}
	void AidMan::updateQuantity() {
		char des[101];
		int found, foundIndex, inputSKU, i, confirmation, addQuantity, subQuantity;
		bool foundExisting = false;
		cout << "Item description: ";
		cin >> des;
		found = list(des);
		if (!found) {
			cout << "No matches found!\n";
		}
		else {
			cout << "Enter SKU: ";
			cin >> inputSKU;
			for (i = 0; i < (m_numProduct - 1) && !foundExisting; i++) {
				if (iproduct[i]->operator==(inputSKU)) {
					foundExisting = true;
					foundIndex = i;
				}
			}
			if (!foundExisting) {
				cout << "SKU not found!";
			}
			else {
				iproduct[foundIndex]->linear(false);
				cout << "1- Add\n2- Reduce\n0- Exit\n> ";
				confirmation = ut.getIntZero(2);
				switch (confirmation) {
				case 0:
					cout << "Aborted!\n";
					break;
				case 1:
					if (iproduct[foundIndex]->qtyNeeded() == iproduct[foundIndex]->qty()) {
						cout << "Quantity Needed already fulfilled!\n";
					}
					else {
						cout << "Quantity to add: ";
						addQuantity = ut.getInt(1, iproduct[foundIndex]->qtyNeeded() - iproduct[foundIndex]->qty());
						iproduct[foundIndex]->operator+=(addQuantity);
						cout << addQuantity << " items added!\n";
					}
					break;
				case 2:
					if (iproduct[foundIndex]->qty() == 0) {
						cout << "Quaintity on hand is zero!\n";
					}
					else {
						cout << "Quantity to reduce: ";
						subQuantity = ut.getInt(1, iproduct[foundIndex]->qty());
						iproduct[foundIndex]->operator-=(subQuantity);
						cout << subQuantity << " items removed!\n";
					}
					break;
				default:
					break;
				}
			}
		}
	}
	void AidMan::sortItem() {
		int i, j;
		iProduct* product;
		product = nullptr;
		for (i = 0; i < m_numProduct; i++) {
			for (j = 0; j < m_numProduct-1; j++) {
				if ((iproduct[j]->qtyNeeded() - iproduct[j]->qty()) < (iproduct[j + 1]->qtyNeeded() - iproduct[j + 1]->qty())) {
					product = iproduct[j];
					iproduct[j] = iproduct[j + 1];
					iproduct[j + 1] = product;
				}
			}
		}
		cout << "Sort completed!\n";
	}
	void AidMan::shipItem() {
		int i, year, month, day, counter;
		counter = 0;
		ut.getSystemDate(&year, &month, &day);
		ofstream file("shippingOrder.txt");
		file << "Shipping Order, Date: " << year << "/";
		file << setw(2) << setfill('0') << month << "/" << day << endl;
		file << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
		file << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl; 
		for (i = 0; i < m_numProduct; i++) {
			if (iproduct[i]->qty() == iproduct[i]->qtyNeeded()) {
				iproduct[i]->linear(true);
				file << setw(4) << setfill(' ');
				file << counter + 1 << " |" << *iproduct[i] << endl;
				counter++;
				remove(i);
			}
		}
		file << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		cout << "Shipping Order for " << counter << " times saved!" << endl;
	}
}





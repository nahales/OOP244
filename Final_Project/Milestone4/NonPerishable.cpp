// Student  Nahal Esmaeili
/////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
// lib includes
#include<iostream>
#include<cstring>
#include<iomanip>
#include "NonPerishable.h"

using namespace std;

namespace ict {

	bool NonPerishable::ok() const {
		if (m_err.isClear())
			return true;
		else
			return false;
	}

	void NonPerishable::error(const char* message) {
		m_err = message;
	}

	std::fstream& NonPerishable::save(std::fstream& file)const {
		file << signature() << "," << sku() << "," << name() << "," << price() << ",";
		file << taxed() << "," << quantity();
		return file;
	}

	std::fstream& NonPerishable::load(std::fstream& file) {
		char fsku[MAX_SKU_LEN];
		char fname[100];
		double fprice;
		bool ftaxed;
		int fquantity;
		file.getline(fsku, MAX_SKU_LEN, ',');
		sku(fsku);
		file.getline(fname, 100, ',');
		name(fname);
		file >> fprice;
		price(fprice);
		file.ignore(1, ',');
		file >> ftaxed;
		taxed(ftaxed);
		file.ignore(1, ',');
		file >> fquantity;
		quantity(fquantity);
		return file;
	}

	std::ostream& NonPerishable::write(std::ostream& os, bool linear)const {
		if (!ok()) {
			os << m_err;
			return os;
		}
		else {
			if (linear) {
				os << left << setw(MAX_SKU_LEN) << setfill(' ') << sku() << "|";
				os << left << setw(20) << setfill(' ') << name() << "|";
				os << right << setw(7) << fixed << setprecision(2) << price() << "|";
				if (taxed()) {
					os << " TN|";
				}
				else {
					os << "  N|";
				}
				os << right << setw(4) << setfill(' ') << quantity() << "|";
				os << right << setw(9) << fixed << setprecision(2) << cost() * quantity() << "|";
			}

			else {
				if (taxed()) {
					os << "Name:" << endl << name() << endl;
					os << "Sku: " << sku() << endl;
					os << "Price: " << price() << endl;
					os << "Price after tax: " << (TAX + 1) * price() << endl;
					os << "Quantity: " << quantity() << endl;
					os << "Total Cost: " << (TAX + 1) * price() * quantity() << endl;
				}

				if (!taxed()) {
					os << "Sku: " << sku() << endl;
					os << "Name: " << name() << endl;
					os << "Price :" << price() << endl;
					os << "Price after tax: N/A" << endl;
					os << "Quantity: " << quantity() << endl;
					os << "Total Cost: " << price() * quantity() << endl;
				}
			}
			return os;
		}
	}

	std::istream& NonPerishable::read(std::istream& is) {
		char isku[MAX_SKU_LEN];
		char iname[100];
		double iprice;
		char itaxed;
		int iquantity;

		m_err.clear();
		if (signature() == 'N')
			cout << "Item Entry:" << endl;
		else
			cout << "Perishable Item Entry:" << endl;
		cout << "Sku: ";
		is >> isku;

		if (is.fail() == false) {
			sku(isku);
		}

		cout << "Name:" << endl;
		is >> iname;
		name(iname);
		cout << "Price: ";
		is >> iprice;
		if (!is.fail()) {
			price(iprice);
			cout << "Taxed: ";
			is >> itaxed;

			if (itaxed == 'Y' || itaxed == 'y' || itaxed == 'N' || itaxed == 'n') {
				if (itaxed == 'y' || itaxed == 'Y'){
					taxed(true);
				}
				else if (itaxed == 'n' || itaxed == 'N') {
					taxed(false);
				}
				cout << "Quantity: ";
				is >> iquantity;

				if (!is.fail()) {
					quantity(iquantity);
				}
				else {
					m_err.message("Invalid Quantity Entry");
					is.setstate(ios::failbit);
				}
			}
			else {
				m_err.message("Invalid Taxed Entry, (y)es or (n)o");
				is.setstate(ios::failbit);
			}
		}
		else {
			m_err.message("Invalid Price Entry");
			is.setstate(ios::failbit);
		}
		return is;
	}

}

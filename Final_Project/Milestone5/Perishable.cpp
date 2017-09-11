// Student  Nahal Esmaeili
/////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
// lib includes
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "Perishable.h"

using namespace std;

namespace ict
{
	Perishable::Perishable() {
		m_expiry.dateOnly(true);
	}

	char Perishable::signature()const {
		return 'P';
	}

	std::fstream& Perishable::save(std::fstream& file)const {
		file << "P" << "," << sku() << "," << name() << "," <<
			price() << "," << taxed() << "," << quantity() << "," << expiry();
		return file;
	}

	std::fstream& Perishable::load(std::fstream& file){
		char fsku[MAX_SKU_LEN];
		char fname[200];
		double fprice;
		int ftaxed = 0;
		int fquantity;
		Date fexpiry;

		file.getline(fsku, MAX_SKU_LEN, ',');
		file.getline(fname, 200, ',');
		file >> fprice;
		file.ignore();
		file >> ftaxed;
		file.ignore();
		file >> fquantity;
		file.ignore();
		file >> fexpiry;
		file.ignore();
		sku(fsku);
		name(fname);
		price(fprice);

		if (ftaxed)
			taxed(true);
		else
			taxed(false);

		quantity(fquantity);
		expiry(fexpiry);

		return file;
	}

	std::ostream& Perishable::write(std::ostream& os, bool linear)const {
		if (m_err.isClear() == false) {
			os << m_err;
		}
		else if (linear) {
			os << left << setw(MAX_SKU_LEN) << setfill(' ') << sku() << "|";
			os << left << setw(20) << setfill(' ') << name() << "|";
			os << right << setw(7) << price() << "|";
			if (taxed()) {
				os << " TP|";
			}
			if (!taxed()) {
				os << "  P|";
			}
			os << right << setw(4) << quantity() << "|";
			os << right << setw(9) << fixed << setprecision(2) << cost() * quantity() << "|";

		}
		else {
			os << "Name:" << endl << name() << endl;
			os << "Sku: " << sku() << endl;
			os << "Price: " << price() << endl;
			if (taxed()) {
				os << "Price after tax: " << fixed << setprecision(2) << cost() << endl;
			}
			if (!taxed()) {
				os << "Price after tax: " << "N/A" << endl;
			}
			os << "Quantity: " << quantity() << endl;
			os << "Total Cost: " << fixed << setprecision(2) << (cost() * quantity()) << endl;
			os << "Expiry date: " << expiry() << endl;
		}
		return os;
	}


	std::istream& Perishable::read(std::istream& is) {
		char isku[MAX_SKU_LEN];
		char iname[100];
		double iprice;
		char itaxed;
		int iquantity;

		m_err.clear();
		
		cout << "Perishable Item Entry:" << endl;
		cout << "Sku: ";
		is >> isku;
		if (!is.fail()) {
			sku(isku);
		}
		sku(isku);
		cout << "Name:" << endl;
		is >> iname;
		name(iname);

		cout << "Price: ";
		is >> iprice;
		
		if (is.fail()) {
			m_err.message("Invalid Price Entry");
			is.setstate(ios::failbit);
		}
		
		else {
			price(iprice);
			cout << "Taxed: ";
			is >> itaxed;

			if (itaxed == 'Y' || itaxed == 'y' || itaxed == 'N' || itaxed == 'n') {
				if (itaxed == 'y' || itaxed == 'Y') {
					taxed(true);
				}
				else if (itaxed == 'n' || itaxed == 'N') {
					taxed(false);
				}
				cout << "Quantity: ";
				is >> iquantity;
				if (!is.fail()) {
					quantity(iquantity);
					cout << "Expiry date (YYYY/MM/DD): ";
					is >> m_expiry;
					if (m_expiry.bad()) {
						if (m_expiry.errCode() == CIN_FAILED) {
							m_err.message("Invalid Date Entry");
							is.setstate(std::ios::failbit);
						}
						else if (m_expiry.errCode() == YEAR_ERROR) {
							m_err.message("Invalid Year in Date Entry");
							is.setstate(std::ios::failbit);
						}
						else if (m_expiry.errCode() == MON_ERROR) {
							m_err.message("Invalid Month in Date Entry");
							is.setstate(std::ios::failbit);
						}
						else if (m_expiry.errCode() == DAY_ERROR) {
							m_err.message("Invalid Day in Date Entry");
							is.setstate(std::ios::failbit);
						}
					}
					else {
						expiry(m_expiry);
					}
				}
				else {
					m_err.message("Invalid Quantity Entry");
				}
			}
			else {
				m_err.message("Invalid Taxed Entry, (y)es or (n)o");
				is.setstate(ios::failbit);
			}
		}
		
		return is;
	}

	const Date& Perishable::expiry()const {
		return m_expiry;
	}

	void Perishable::expiry(const Date &E1){
		m_expiry = E1;
	}
}
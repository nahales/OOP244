// Student  Nahal Esmaeili
/////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS  
// Lib includes
#include <iostream>
#include <cstring>
// inlcude Item and POS header files
#include "Item.h"
#include "POS.h"
#include "PosIO.h"

using namespace std;
namespace ict {
	// class Item implementaion
	Item::Item() {
		m_sku[0] = '\0';
		m_name = nullptr;
		m_price = 0.0;
		m_taxed = 0;
		m_quantity = 0;
	};

	Item::Item(const char* sku1, const char* name1, double price1, bool taxed1) : m_name((char*)0) {
		sku(sku1);
		name(name1);
		price(price1);
		taxed(taxed1);
	};

	//copy constructor
	Item::Item(const Item& src) : m_name((char*)0) {
		sku(src.m_sku);
		name(src.m_name);
		price(src.m_price);
		taxed(src.m_taxed);
		quantity(src.m_quantity);
	};

	Item& Item::operator=(const Item& I1) {
		if(!isEmpty()){
			sku(I1.m_sku);
			name(I1.m_name);
			price(I1.m_price);
			taxed(I1.m_taxed);
			quantity(I1.m_quantity);
		}
			return *this;
	}

	Item::~Item() {
		delete[] m_name;
		m_name = 0;
	}

	//setter
	void Item::sku(const char* sku) {
		strncpy(m_sku, sku, MAX_SKU_LEN);
		m_sku[MAX_SKU_LEN] = '\0';

	}

	void Item::price(double price) {
		m_price = price;

	}

	void Item::name(const char* name) {
		m_name = new char[strlen(name)+1];
		strcpy(m_name, name);
		m_name[strlen(name) + 1] = '\0';
	}

	void Item::taxed(bool taxed) {
		m_taxed = taxed;
	}

	void Item::quantity(int quantity) {
		m_quantity = quantity;
	}

	//getters
	const char* Item::sku() const {
		return m_sku;
	}

	double Item::price() const {
		return m_price;
	}

	const char* Item::name() const {
		return m_name;
	}

	const bool Item::taxed() const {
		return m_taxed;
	}

	int Item::quantity() const {
		return m_quantity;
	}

	double Item::cost() const {
		if (taxed())
			return m_price*(1 + TAX);
		else
			return m_price;
	}

	bool Item::isEmpty() const {
		if (m_price == 0 && m_quantity == 0)
			return true;
		else
			return false;
	}

	//operators
	bool Item::operator==(const char* sku) const {
		if (strcmp(m_sku, sku) == 0)
			return true;
		else
			return false;
	}

	int Item::operator+=(int quantity) {
		m_quantity += quantity;
		return m_quantity;
	}

	int Item::operator-=(int quantity) {
		m_quantity -= quantity;
		return m_quantity;
	}

	double operator+=(double& d, const Item& I1) {
		d += (I1.cost() * I1.quantity());
		return d;
	}

	std::istream& operator >> (istream& is, Item& I1) {
			return I1.read(is);
	}

	std::ostream& operator<<(ostream& os, const Item& I1) {
			return I1.write(os, true);
	}

	std::ostream& Item::write(std::ostream& os, bool linear)const
	{
		return os;
	}

	std::istream& Item::read(std::istream& is)
	{
		return is;
	}
}

		

		
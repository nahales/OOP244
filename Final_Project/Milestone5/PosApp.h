// Student  Nahal Esmaeili
/////////////////////////////////////////////////////////////////

#pragma once
#ifndef ICT_POSAPP_H_
#define ICT_POSAPP_H_
#include <iostream>
#include <fstream>
#include "Item.h"

namespace ict
{
	class PosApp {
	private:
		char m_filename[128];
		char m_billfname[128];
		Item* m_items[MAX_NO_ITEMS];
		int m_noOfItems;
		int menu();
		void deallocateItems();
		void loadRecs();
		void saveRecs();
		int searchItems(const char*)const;
		void updateQty();
		void addItem(bool);
		void listItems()const;
		void truncateBillFile();
		void showBill();
		void addToBill(Item& I);
		void POS();

	public:
		PosApp(const char*, const char*);
		void run();
	};
}
#endif
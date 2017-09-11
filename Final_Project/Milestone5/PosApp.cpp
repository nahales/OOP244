// Student  Nahal Esmaeili
/////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <cstring>
#include "PosApp.h"
#include "Perishable.h"
#include "Item.h"

using namespace std;
namespace ict
{
	PosApp::PosApp(const char* filename, const char* billfname) {
		strcpy(m_filename, filename);
		strcpy(m_billfname, billfname);
		m_noOfItems = 0;
		loadRecs();
	}

	int PosApp::menu() {
		int selectedOption;
		cout << "The Sene-Store" << endl;
		cout << "1- List items" << endl;
		cout << "2- Add Perishable item" << endl;
		cout << "3- Add Non-Perishable item" << endl;
		cout << "4- Update item quantity" << endl;
		cout << "5- Show Item" << endl;
		cout << "6- POS" << endl;
		cout << "0- exit program" << endl;
		cout << "> ";
		cin >> selectedOption;
		cout << endl;
		if (cin.fail()) {
			if (selectedOption > 6) {
				cin.clear();
				cin.ignore(1000, '\n');
				selectedOption = -1;
			}
		}
		return selectedOption;
	}

	void PosApp::deallocateItems() {
		for (int i = 0; i < m_noOfItems; i++) {
			delete[] m_items[i];
			m_items[i] = NULL;
		}
		m_noOfItems = 0;
	}

	void PosApp::loadRecs() {
		int i = 0;
		char itemType;
		std::fstream datafile;
		datafile.open(m_filename, ios::in);
		if (datafile.fail()) {
			datafile.clear();
			datafile.close();
			datafile.open(m_filename, ios::out);
			datafile.close();
		}
		else {
			while (!datafile.fail()) {
				if (!m_items[i]) {
					delete m_items[i];
				}
				datafile >> itemType;
				if (itemType == 'P') {
					Perishable* perishable = new Perishable;
					m_items[i] = perishable;
				}
				else if (itemType == 'N') {
					NonPerishable* product = new NonPerishable;
					m_items[i] = product;
				}
				if (itemType == 'P' || itemType == 'N') {
					datafile.get(itemType);
					m_items[i]->load(datafile);
					i++;
				}
			}
			m_noOfItems = i;
		}
		datafile.close();
	}

	void PosApp::saveRecs() {
		std::fstream datafile;
		datafile.open(m_filename, ios::out);
		for (int i = 0; i < m_noOfItems; i++) {
			if (m_items[i]->quantity() > 0) {
				m_items[i]->save(datafile);
				datafile << endl;
			}
		}
		datafile.close();
		loadRecs();
	}

	int PosApp::searchItems(const char* sku)const {
		int foundItem = -1;
		for (int i = 0; i < m_noOfItems; i++) {
			if (*m_items[i] == sku) {
				foundItem = i;
				break;
			}
		}
		return foundItem;
	}

	void PosApp::updateQty() {
		char isku[1000];
		int foundIndex;
		int nOfPurchItems = 0;
		cout << "Please enter the SKU: ";
		cin >> isku;
		foundIndex = searchItems(isku);
		if (foundIndex == -1) {
			cout << "Not found!" << endl << endl;
		}
		else {
			m_items[foundIndex]->write(cout, false);
			cout << endl;
			cout << "Please enter the number of purchased items: ";
			cin >> nOfPurchItems;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid Quantity value!" << endl << endl;
			}
			else {
				*m_items[foundIndex] += nOfPurchItems;
				cout << "Updated!" << endl << endl;
			}
		}
	}

	void PosApp::addItem(bool isPerishable) {
		if (isPerishable) {
			Perishable* pItem = new Perishable;
			pItem->read(cin);
			if (cin.fail()) {
				cin.clear();
				pItem->write(cout, true);
			}
			else {
				fstream datafile;
				datafile.open(m_filename, ios::out);
				m_items[m_noOfItems] = pItem;
				pItem->save(datafile);
				m_noOfItems++;
				datafile.close();
				cout << "Item added." << endl << endl;
			}
		}
		if (!isPerishable) {
			NonPerishable* npItem = new NonPerishable;
			npItem->read(cin);
			if (cin.fail()) {
				cin.clear();
				npItem->write(cout, true);
				cout << endl;
			}
			else {
				fstream datafile;
				datafile.open(m_filename, ios::out);
				m_items[m_noOfItems] = npItem;
				npItem->save(datafile);
				m_noOfItems++;
				datafile.close();
				cout << "Item added." << endl << endl;
			}
		}
	}

	void PosApp::listItems()const {
		double totalCost = 0;
		cout << " Row " << "|";
		cout << " SKU    " << "|";
		cout << " Item Name          " << "|";
		cout << " Price " << "|";
		cout << "TX " << "|";
		cout << "Qty " << "|";
		cout << "   Total " << "|" << endl;
		cout << "-----|--------|--------------------|-------|---|----|---------|" << endl;
		for (int i = 0; i < m_noOfItems; i++) {
			cout << right << setfill(' ') << setw(4) << i + 1 << " | " << *m_items[i] << endl;
			totalCost += m_items[i]->cost() * m_items[i]->quantity();
		}
		cout << "-----^--------^--------------------^-------^---^----^---------^" << endl;
		cout << setw(48) << right << "Total Asset: $  |" << setw(14) << right << fixed << setprecision(2) << totalCost << "|" << endl;
		cout << "-----------------------------------------------^--------------^" << endl << endl;
	}

	void PosApp::truncateBillFile() {
		std::fstream datafile;
		datafile.open(m_billfname, ios::out | ios::trunc);
		datafile.close();
	}

	void PosApp::showBill() {
		char itemType;
		double totalCost = 0;
		Item* pItem = NULL;
		Item* npItem = NULL;
		std::fstream datafile;
		datafile.open(m_billfname, ios::in);
		if (datafile.fail()) {
			datafile.clear();
			datafile.close();
			datafile.open(m_billfname, ios::out);
			datafile.close();
		}
		else {
			cout << "v--------------------------------------------------------v" << endl;
			cout << "| " << Date() << setfill(' ') << setw(39) << "|" << endl;
			cout << "| SKU    | Item Name          | Price |TX |Qty |   Total |" << endl;
			cout << "|--------|--------------------|-------|---|----|---------|" << endl;
			while (!datafile.eof()) {
				datafile >> itemType;
				datafile.ignore(1);
				if (!datafile.eof()) {
					if (itemType == 'P') {
						cout << "| ";
						pItem = new Perishable();
						pItem->load(datafile);
						pItem->write(std::cout, true);
						cout << endl;
						totalCost += pItem->cost();
					}
					else if (itemType == 'N') {
						cout << "| ";
						npItem = new NonPerishable();
						npItem->load(datafile);
						npItem->write(std::cout, true);
						cout << endl;
						totalCost += npItem->cost();
					}
				}
			}
			cout << "^--------^--------------------^-------^---^----^---------^" << endl;
			cout << "| " << setw(41) << "Total: $  |" << setw(14) << setprecision(2) << totalCost << "|" << endl;
			cout << "^-----------------------------------------^--------------^" << endl;
			cout << endl;
		}
		datafile.clear();
		datafile.close();
		truncateBillFile();
	}

	void PosApp::addToBill(Item& I) {
		int iquantity;
		std::fstream datafile;
		iquantity = I.quantity();
		I.quantity(1);
		datafile.open(m_billfname, ios::out | ios::app);
		if (iquantity > 0) {
			iquantity--;
		}
		I.save(datafile);
		datafile << endl;
		I.quantity(iquantity);
		datafile.close();
		saveRecs();
	}

	void PosApp::POS() {
		int i = 0;
		char sku[MAX_SKU_LEN + 1];
		do {
			sku[0] = '\0';
			cout << "Sku: ";
			cin.getline(sku, MAX_SKU_LEN);
			i = searchItems(sku); 
			if (i != -1) {
				cout << "v------------------->" << endl
					<< "| " << m_items[i]->name() << endl 
					<< "^------------------->" << endl;
				addToBill(*m_items[i]);
			}
			else if (sku[0] != '\0') {
				cout << "Not found!" << endl;
			}
		} while (sku[0] != '\0');
		showBill();
	}

	void PosApp::run() {
		bool userInput = true;
		while (userInput){
			int menueOption = menu();
			switch (menueOption){
			case 1:
				listItems();
				break;
			case 2:
				addItem(true);
				break;
			case 3:
				addItem(false);
				break;
			case 4:
				updateQty();
				break;
			case 5:
				char sku[MAX_SKU_LEN + 1];
				int searchedItem;
				cout << "Please enter the SKU: ";
				cin >> sku;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(1000, '\n');
				}
				else {
					searchedItem = searchItems(sku);
					if (searchedItem == -1) {
						cout << "Not found!" << endl;
					}
					else {
						cout << "v-----------------------------------v" << endl;
						m_items[searchedItem]->write(cout, false);
						cout << "^-----------------------------------^" << endl << endl;
					}
				}
				break;
			case 6:
				cin.ignore(1000, '\n');
				POS();
				break;
			case 0:
				cout << "Goodbye!" << endl;
				userInput = false;
				break;
			default:
				cout << "===Invalid Selection, try again===" << endl << endl;
				break;
			}
		}
	}	
}

/*
ouputs:
-------------------------------------
update:
Please enter the SKU: 1313
Name:
Paper Tissue
Sku: 1313
Price: 1.22
Price after tax: 1.38
Quantity: 194
Total Cost: 267.45

Please enter the number of purchased items: 12
Updated!

------------------------------
Please enter the SKU: 3434
Not found!

-------------------------------------
add item:
Perishable Item Entry:
Sku: 5656
Name:
Honey
Price: 12.99
Taxed: y
Quantity: 12
Expiry date (YYYY/MM/DD): 1200/10/12
Invalid Year in Date Entry

Perishable Item Entry:
Sku: 5656
Name:
Honey
Price: 12.99
Taxed: y
Quantity: 12
Expiry date (YYYY/MM/DD): 2017/5/15
Item added.

--------------------------------------------
list item:
Row | SKU    | Item Name          | Price |TX |Qty |   Total |
-----|--------|--------------------|-------|---|----|---------|
1 | 1234   |Milk                |   3.99|  P|   2|     7.98|
2 | 3456   |Paper Cups          |   5.99| TN|  38|   257.21|
3 | 4567   |Butter              |   4.56| TP|   9|    46.38|
4 | 1212   |Salted Butter       |   5.99|  P| 111|   664.89|
5 | 1313   |Paper Tissue        |   1.22| TN| 206|   283.99|
6 | 5656   |Honey               |  12.99| TP|  12|   176.14|
-----^--------^--------------------^-------^---^----^---------^
Total Asset: $  |       1436.59|
-----------------------------------------------^--------------^


--------------------------------------
printbill:
v--------------------------------------------------------v
| 2017/04/02, 12:42                                      |
| SKU    | Item Name          | Price |TX |Qty |   Total |
|--------|--------------------|-------|---|----|---------|
| 1212   |Salted Butter       |   5.99|  P|   1|     5.99|
| 1313   |Paper Tissue        |   1.22| TN|   1|     1.38|
| 5656   |Honey               |  12.99| TP|   1|    14.68|
^--------^--------------------^-------^---^----^---------^
|                               Total: $  |         22.05|
^-----------------------------------------^--------------^

-------------------------------------------------------
POS:
Sku: 1212
v------------------->
| Salted Butter
^------------------->
Sku: 1212
v------------------->
| Salted Butter
^------------------->
Sku: 1313
v------------------->
| Paper Tissue
^------------------->
Sku: 1234
v------------------->
| Milk
^------------------->
Sku: 7654
Not found!
Sku: 5656
v------------------->
| Honey
^------------------->
Sku:
v--------------------------------------------------------v
| 2017/04/02, 12:58                                      |
| SKU    | Item Name          | Price |TX |Qty |   Total |
|--------|--------------------|-------|---|----|---------|
| 1212   |Salted Butter       |   5.99|  P|   1|     5.99|
| 1212   |Salted Butter       |   5.99|  P|   1|     5.99|
| 1313   |Paper Tissue        |   1.22| TN|   1|     1.38|
| 1234   |Milk                |   3.99|  P|   1|     3.99|
| 5656   |Honey               |  12.99| TP|   1|    14.68|
^--------^--------------------^-------^---^----^---------^
|                               Total: $  |         32.03|
^-----------------------------------------^--------------^

------------------------------------------------------
run:
The Sene-Store
1- List items
2- Add Perishable item
3- Add Non-Perishable item
4- Update item quantity
5- Show Item
6- POS
0- exit program
> 5

Please enter the SKU: 5656
v-----------------------------------v
Name:
Honey
Sku: 5656
Price: 12.99
Price after tax: 14.68
Quantity: 10
Total Cost: 146.79
Expiry date: 2017/05/15
^-----------------------------------^

The Sene-Store
1- List items
2- Add Perishable item
3- Add Non-Perishable item
4- Update item quantity
5- Show Item
6- POS
0- exit program
> 5

Please enter the SKU: 12345
Not found!

The Sene-Store
1- List items
2- Add Perishable item
3- Add Non-Perishable item
4- Update item quantity
5- Show Item
6- POS
0- exit program
> five

===Invalid Selection, try again===

The Sene-Store
1- List items
2- Add Perishable item
3- Add Non-Perishable item
4- Update item quantity
5- Show Item
6- POS
0- exit program
> 0

Goodbye!

*/
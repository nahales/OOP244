// Student  Nahal Esmaeili
/////////////////////////////////////////////////////////////////

#ifndef ICT_ITEM_H__
#define ICT_ITEM_H__
// inlcude PosIO and POS header files
#include "PosIO.h"
#include "POS.h"
using namespace std;
namespace ict{
  // class Item
	class Item : public PosIO 
	{
		char m_sku[MAX_SKU_LEN+1]; //This character array holds the SKU (barcode) of the items as a string.
		char* m_name; //This character pointer points to a dynamically allocated string that holds the Item’s name.
		double m_price; //This variable holds the Item’s Price.
		bool m_taxed; //This variable is true if this item is taxed, false otherwise.
		int m_quantity; //This variable holds the Item’s on-hand (current) quantity.
		
	public:
		Item(); //This constructor sets the item to a safe recognizable empty state. All numeric values are set to zero in this state.
		Item(const char*, const char*, double, bool = true); 
		Item(const Item&);
		Item& operator=(const Item&);
		virtual ~Item();
		
	//setters
		//void set(const char* sku, const char* name, double price, int quantity, bool taxed);
		void sku(const char*);
		void name(const char*);
		void price(double);
		void taxed(bool);
		void quantity(int);
	//getters
		const char* sku() const;
		const char* name() const;
		double price() const;
		const bool taxed() const;
		int quantity() const;
		double cost() const;
		bool isEmpty() const;

		bool operator==(const char*) const;
		int operator+=(int);
		int operator-=(int);
		std::ostream& write(std::ostream&, bool)const;
		std::istream& read(std::istream&);
	};
  // end class Item
  // operator += 
  double operator+=(double&, const Item&);

  // operator << and operator >>
  std::istream& operator>>(std::istream&, Item&);
  std::ostream& operator<<(std::ostream&, const Item&);
}
#endif
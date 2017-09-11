#include "Account.h"

using namespace std;

namespace ict{ 
	
	// constructor   
	Account::Account(double srcBalance){
		if (srcBalance >= 0) {
			setBalance(srcBalance);
		}
		else {
			setBalance(1.0);
		}
	}

	// credit (add) an amount to the account balance
	void Account::credit(double crAmount) {
		setBalance(balance + crAmount);
	}

	// debit (subtract) an amount from the account balance return bool
	bool Account::debit(double dbAmount) {
		if (dbAmount <= balance) {
			setBalance(balance - dbAmount);
			return true;
		}
		else {
			return false;
		}

	}

	double Account::getBalance() const
	{
		return balance;
	} 

	void Account::setBalance( double srcBalance )
	{
		balance = srcBalance;
	} 

	void Account::display(ostream& os) const{
		os << balance;
	}
}
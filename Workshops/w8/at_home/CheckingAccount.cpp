#include "CheckingAccount.h"

using namespace std;

namespace ict{    
	
	// TODO: define CheckingAccount class member functions here  
	CheckingAccount::CheckingAccount(double srcBalance, double srcTransFee) : Account(srcBalance) {
		if (srcTransFee < 0) {
			transactionFee = 0;
		}
		else {
			transactionFee = srcTransFee;
		}
	};

	void CheckingAccount::chargeFee(double srcTransFee) {
		double srcBalance = getBalance() - srcTransFee;
		setBalance(srcBalance);
	}

	bool CheckingAccount::debit(double dbAmount) {
		if (Account::debit(dbAmount)) {
			chargeFee(this->transactionFee);
			return true;
		}
		else {
			return false;
		}
	}

	void CheckingAccount::credit(double crAmount) {
		Account::credit(crAmount);
		chargeFee(this->transactionFee);
	}

	void CheckingAccount::display(std::ostream& os) const {
		os << "Account type: " << "Checking" << endl;
		os << "Balance: " << "$ ";
		os.setf(ios::fixed);
		os.precision(2);
		Account::display(os);
		os << endl;
		os << "Transaction Fee: " << transactionFee << endl;
	}

}
#include "SavingsAccount.h"
#include "Account.h"

using namespace std;

namespace ict {

	// TODO: Implement SavingsAccount member functions here
	SavingsAccount::SavingsAccount(double srcBalance, double interest) : public Account(srcBalance)
	{
		if (interest < 0)
			interestRate = 0.0;
		else
			interestRate = interest;
	};


	double SavingsAccount::calculateInterest() {
		double calcBalance = getBalance() * interestRate;
		return calcBalance;

	}

	void SavingsAccount::display(std::ostream& os) const {
		os << "Account type: " << "Saving" << endl;
		os << "Balance: " << "$ ";
		os.setf(ios::fixed);
		os.precision(2);
		Account::display(os);
		os << endl;
		os << "Interest Rate (%): " << this->interestRate * 100 << endl;
	}
}
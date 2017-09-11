#ifndef ICT_CHECKINGACCOUNT_H__
#define ICT_CHECKINGACCOUNT_H__

#include "Account.h"

using namespace std;

namespace ict{
	class CheckingAccount : public Account {
		private:
			double transactionFee;

			// TODO: chargeFee subtract transaction fee form the balance
			void chargeFee(double);
		public:

			// TODO: constructor initializes balance and transaction fee
			CheckingAccount(double, double);
			// TODO: Write a function prototype to override credit function
			void credit(double);
			// TODO: Write a function prototype to override debit function
			bool debit(double);
			// TODO: Write a function prototype to  override display function
			void display(std::ostream& os) const;
	};
};
#endif


#include <iostream>
#include <string.h>
#include "Contact.h"

using namespace std;
namespace communication{

	//default constructor
	Contact::Contact() {
		m_name[0] = '\0';
		m_noOfPhoneNumbers = 0; 
	}

	Contact::Contact(const char* n, long long* phoneNumbers, int count) {
		bool valid = n != nullptr && strlen(n) > 0 && count >= 0;
		int j = 0;
		if (valid) {
			m_noOfPhoneNumbers = 0;
			for (int i = 0; i < count; i++) {
				if (isValid(phoneNumbers[i]))
					m_noOfPhoneNumbers++;
			}
			m_phoneNumbers = new long long[m_noOfPhoneNumbers];
			for (int i = 0; i < count; i++){
				if (isValid (phoneNumbers[i])){
					m_phoneNumbers[j] = phoneNumbers[i];
					j++;
				}
			}
			strncpy(m_name, n, strlen(m_name) - 1);
		}
		else {
			m_name[0] = '\0';
			m_noOfPhoneNumbers = 0;
		}
	}

	bool Contact::isValid(long long input) const {
		//for example, input = 1 234 567 8901 
		if (input <= 0)
			return false;
		else {
			input /= 1000000; //input is now: 1 234 5
			if (input % 10 == 0 || input <= 0) //check the last digit and to see if # is 0;
				return false;
			else {
				input /= 1000; //input is now: 12
				if (input % 10 == 0 || input <= 0) //check first digit of area code
					return false;
				else {
					input /= 10; //input is now: 1
					if (input <= 0 || input >= 100) //check the length of country code
						return false; 
					else {
						return true;
					}
				}
			}
		}
	}

	Contact::~Contact() {
		delete [] m_phoneNumbers;
	}

	bool Contact::isEmpty() const {
		if (m_name[0] == '\0' && m_noOfPhoneNumbers == 0) {
		
				return true;
			}
			else {
				return false;
			}

		}

	void Contact::display() const {
		if (Contact::isEmpty())
			cout << "Empty contact!" << endl;
		else {
			cout << m_name << endl;
			for (int i = 0; i < m_noOfPhoneNumbers; i++) {
				cout << "(+"
					<< m_phoneNumbers[i] / 10000000000
					<< ") "
					<< m_phoneNumbers[i] % 10000000000 / 10000000
					<< " "
					<< m_phoneNumbers[i] % 10000000 / 10000
					<< "-"
					<< m_phoneNumbers[i] % 10000 << endl;
			}
		}
	}
}
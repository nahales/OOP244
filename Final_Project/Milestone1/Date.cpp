// Student  Nahal Esmaeili
/////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
#include <string>
#include "Date.h"
#include "POS.h"

using namespace std;
namespace ict{

	Date::Date() {
		dateOnly(false);
		set();
	};
	Date::Date(int year, int mon, int day) {
		dateOnly(true);
		int hour = 0;
		int min = 0;
		set(year, mon, day, hour, min);
	};

	Date::Date(int year, int mon, int day, int hour, int min) {
		dateOnly(false);
		set(year, mon, day, hour, min);
	};

	
	void Date::set(){
		time_t t = time(NULL);
		tm lt = *localtime(&t);
		m_day = lt.tm_mday;
		m_mon = lt.tm_mon + 1;
		m_year = lt.tm_year + 1900;
		if (dateOnly()){
		  m_hour = m_min = 0;
		}
		else{
		  m_hour = lt.tm_hour;
		  m_min = lt.tm_min;
		}
	}

	void Date::set(int year, int mon, int day, int hour, int min) {
			m_year = year;
			m_mon = mon;
			m_day = day;
			m_hour = hour;
			m_min = min;
			errCode(NO_ERROR);
	}

	int Date::value()const {
		return m_year * 535680 + m_mon * 44640 + m_day * 1440 + m_hour * 60 + m_min;
	}

	int Date::mdays()const{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
		mon--;
		return days[mon] + int((mon == 1)*((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
	}

	bool Date::operator==(const Date& D) const {
		if (this->value() == D.value())
			return true;
		else
			return false;
	}

	bool Date::operator!=(const Date& D) const {
		if (this->value() != D.value())
			return true;
		else
			return false;
	}

	bool Date::operator<(const Date& D) const {
		if (this->value() < D.value())
			return true;
		else
			return false;
	}

	bool Date::operator>(const Date& D) const {
		if (this->value() > D.value())
			return true;
		else
			return false;
	}

	bool Date::operator<=(const Date& D) const {
		if (this->value() <= D.value())
			 return true;
		 else
			 return false;
	}
  
	bool Date::operator>=(const Date& D) const {
		if (this->value() >= D.value())
			return true;
		else
			return false;
	}

	void Date::errCode(int errorCode) {
		m_readErrorCode = errorCode;
	}

	int Date::errCode()const {
		return m_readErrorCode;
	}

	bool Date::bad()const {
		if (m_readErrorCode != 0)
			return true;
		else
			return false;
	}

	void Date::dateOnly(bool value) {
		m_dateOnly = value;
		if (m_dateOnly) {
			m_hour = 0;
			m_min = 0;
		}
	}

	bool Date::dateOnly()const {
		return m_dateOnly;
	}

	std::istream& Date::read(std::istream& is = std::cin) {
		char dummy;

		if (dateOnly()){
			is >> m_year >> dummy >> m_mon >> dummy >> m_day;

			if (is.fail() || is.bad()) 
				errCode(CIN_FAILED);
			else {
				if (m_year < MIN_YEAR || m_year > MAX_YEAR)
					errCode(YEAR_ERROR);
				else {
					if (m_mon < 1 || m_mon > 12)
						errCode(MON_ERROR);
					else {
						if (m_day < 1 || m_day > mdays())
							errCode(DAY_ERROR);
					}
				}
			}
		}
		else if (!dateOnly()) 
		{

			is >> m_year >> dummy >> m_mon >> dummy >> m_day >> dummy >> m_hour >> dummy >> m_min;

			if (is.fail() || is.bad()) {
				errCode(CIN_FAILED);
			}
			else {
				if (m_year < MIN_YEAR || m_year > MAX_YEAR)
					errCode(YEAR_ERROR);
				else {
					if (m_mon < 1 || m_mon > 12)
						errCode(MON_ERROR);
					else {
						if (m_day < 1 || m_day > mdays())
							errCode(DAY_ERROR);
						else {
							if (m_hour < 0 || m_hour > 23)
								errCode(HOUR_ERROR);
							else {
								if (m_min < 0 || m_min > 59)
									errCode(MIN_ERROR);
							}
						}
					}
				}
			}
		}

		return is;
	}

	std::ostream& Date::write(std::ostream& os = std::cout)const {
		if (dateOnly()) {
			os << m_year << "/" << setfill('0') << setw(2) << m_mon << "/" << setfill('0') << setw(2) << m_day;
		}
		else {
			os << m_year << "/" << setfill('0') << setw(2) << m_mon << "/" << setfill('0') << setw(2) << m_day << ", " << setfill('0') << setw(2) << m_hour << ":" << setfill('0') << setw(2) << m_min;
		}
		return os;
	}


	std::istream& operator >> (std::istream& is, Date& D) {
		D.read(is);
		return is;
	}

	std::ostream& operator<<(std::ostream& os, const Date& D) {
		D.write(os);
		return os;
	}
}




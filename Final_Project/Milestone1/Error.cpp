// Student  Nahal Esmaeili
/////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS 
#include "Error.h"
#include <cstring>
using namespace std;
namespace ict
{
	Error::Error()
	{
		m_message = nullptr;
	}

	Error::Error(const char* errorMessage)
	{
		m_message = nullptr;
		message(errorMessage);
	}

	Error::~Error()
	{
		delete[] m_message;
	}

	void Error::operator=(const char* errorMessage)
	{
		clear();
		message(errorMessage);
	}

	void Error::clear()
	{
		if (isClear())
		{
			delete m_message;
		}

		else
		{
			delete[] m_message;
			m_message = nullptr;
		}
	}

	void Error::message(const char* value)
	{
		clear();
		char* temporary = new char[strlen(value) + 1];

		strcpy(temporary, value);
		m_message = temporary;
	}

	bool Error::isClear() const
	{
		return m_message == nullptr;
	}

	Error::operator const char*() const
	{
		return m_message;
	}

	Error::operator bool() const
	{
		return m_message == nullptr;
	}

	std::ostream& operator<<(std::ostream& os, const Error& error) 
	{
		if (!error.isClear()) 
		{
			os << error.operator const char*();
		}

		return os;
	}
}
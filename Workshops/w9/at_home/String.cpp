#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include "String.h"


using namespace std;

namespace sict{
    
    
    //////////////////////////////////////////////////////
    //
    // Default Constructor
    // String::String(int capacity);
    //
    // initialize the string with an internal buffer capacity of 
    // "capacity." 
    // default capacity is 1 (minimum needed for an empty string)
    //
    // 
    String::String(int capacity)
	{
		m_capacity = capacity;
		m_pString = new char[m_capacity];
		strcpy(m_pString, "");
    }


    //////////////////////////////////////////////////////
    //
    // String::String(const char* p, int capacity);
    //
    // Construct a String from a char array
    // Should initialize the internal buffer to at least 
    // the length of the string need to hold pSource, 
    // or capacity, whichever is greater.
    //
    // 
    String::String(const char* pSource, int capacity)
	{
		int tempCap = strlen(pSource);
		if (tempCap >= capacity) {
			m_capacity = strlen(pSource) + 1;
		}
		else {
			m_capacity = capacity;
		}
		m_pString = new char[m_capacity];
		strcpy(m_pString, pSource);
    }


    //////////////////////////////////////////////////////
    //
    // String::String(const String &s, int capacity);
    //
    // Copy constructor
    //
    // Construct a String from another String
    //
    // 
    String::String(const String& other, int capacity) 
    {
		int tempCap = strlen(other.m_pString);
		if (tempCap >= capacity) {
			m_capacity = strlen(other.m_pString) + 1;
		}
		else {
			m_capacity = capacity;
		}
		m_pString = new char[m_capacity];
		strcpy(m_pString, other.m_pString);
    }

    
    //////////////////////////////////////////////////////
    //
    // String::resize(int newsize)
    //
    // resize the internal buffer to the value given
    // do NOT shrink the string buffer smaller than 
    // that needed to hold the existing string!
    // (length + 1);
    //    
    void String::resize(int newsize)
    {
		String tempStr(*this);
		if (newsize >= m_capacity + 1) {
			m_capacity = newsize;
			m_pString = new char[newsize];
			strcpy(m_pString, tempStr.m_pString);
		}
    }
                                    
  
    //////////////////////////////////////////////////////
    //
    // String::operator=(const String& other)
    // 
    // Assignment operator
    // copy string "other" to this object
    //   
    // 
    String& String::operator=(const String& other)
    {
		m_capacity = other.m_capacity;
		m_pString = new char[m_capacity];
		strcpy(m_pString, other.m_pString);
		return *this;
    }


    //////////////////////////////////////////////////////
    //
    // String::~String
    // 
    // destructor
    // 
    // clean up the internal string buffer  
    // 
    String::~String()
    {
		delete[] m_pString;
    }


    //////////////////////////////////////////////////////
    //
    // String::length()
    // 
    // return the length of the string
    // 
    // 
    int String::length() const
    {
		return strlen(m_pString);
    }


    //////////////////////////////////////////////////////
    //
    // String::operator const char*() const
    // 
    // convert the String to a char*
    // 
    // 
    String::operator const char *() const
    {
		return m_pString;
    }


    //////////////////////////////////////////////////////
    //
    // String::empty()
    // 
    // 
    // returns true if the string is empty
    // i.e. either the first char is \0, or 
    // length is 0.
    bool String::empty() const
    {
		if (strlen(m_pString) == 0) {
			return true;
		}
		else {
			return false;
		}
    }
    

    //////////////////////////////////////////////////////
    //
    // String::operator bool()
    // 
    // same as empty(), just wrapped in an operator
    // 
    //     
    String::operator bool() const
    {
		if (strcmp(m_pString, "") == 0) {
			return false;
		}
		else {
			return true;
		}
    }
     
     
    //////////////////////////////////////////////////////
    //
    // String::operator==(const String& s2) const
    // 
    // returns true if *this == s2.
    // You can use the strcmp function to check if 
    // two strings are equal, or write your own
    // treating the string as a char-array
    //      
    bool String::operator==(const String& s2) const
    {
		if (strcmp(m_pString, s2) == 0) {
			return true;
		}
		else {
			return false;
		}
    }
    
    
    //////////////////////////////////////////////////////
    //
    // String::operator+=(const String& s2)
    // 
    // Concatenates s2 to the end of *this
    //
    // implements *this = (*this + s2)
    // return *this
    // 
    // 
    String& String::operator+=(const String& s2)
    {
		String tempStr(*this);
		m_capacity += s2.m_capacity;
		m_pString = new char[m_capacity];
		strcpy(m_pString, tempStr.m_pString);
		strcat(m_pString, s2.m_pString);
		return *this;
    }
    
    
    //////////////////////////////////////////////////////
    //
    // String::operator+(const String& s2) const
    // 
    // implements the operator (*this + s2)
    // returns the expression
    // DOES NOT MODIFY *this
    // 
    // 
    String String::operator+(const String& s2) const
    {
		String tempStr(*this);

		tempStr.m_capacity += s2.m_capacity;
		tempStr.resize(tempStr.m_capacity + 1);

		strcat(tempStr.m_pString, s2.m_pString);

		return tempStr;
    }
    

    //////////////////////////////////////////////////////
    //
    // String::operator+=(char c)
    // 
    // Adds a single char c to the end of the string in *this
    // Grows the string buffer if necessary.
    //  
    String& String::operator+= (char c)
    {
		int len = strlen(m_pString);

		resize(len + 2);
		m_pString[len] = c;

		m_pString[len + 1] = '\0';

		return *this;
    }
    

    //////////////////////////////////////////////////////
    //
    // String::substr
    // 
    // Returns a substring of the current string. In case of error
    // return an empty String() object instead.
    // 
    // return the string slice starting at index, at most len characters
    // 
    // both index and len have to lie inside the string. If they do not, then 
    // that is an error
    // 
    String String::substr(int index, int len) const
    {
		if (index + len > length())
			return String();
		else
		{
			String tempStr(len);
			int v, i = 0;
			for (v = index; v < index + len; v++, i++)
				tempStr.m_pString[i] = m_pString[v];

			return tempStr;

		}
    }


    //////////////////////////////////////////////////////
    //
    // operator<<
    // 
    // Print the string to the output stream
    // 
    // clean up the internal string buffer  
    // 
    std::ostream& operator<<(std::ostream& ostream, const String &s)
    {
		ostream << s.operator const char *();
		return ostream;
    }


    //////////////////////////////////////////////////////
    //
    // operator>>
    // 
    // Input a string from an input stream into the String s
    // 
    // Note: the input can be ANY length in character. You will need to 
    // read it one char at a time. 
    // 
    std::istream& operator>>(std::istream& istream, String &s)
    {
        s = "";
        char tempC = 0;
        do
        {
            tempC = istream.get();
            if (tempC != '\n')
            {
                s += tempC;
            }
            else
                break;
        } while(1);
        return istream;
    }

  
}

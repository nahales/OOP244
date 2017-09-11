// Student  Nahal Esmaeili
/////////////////////////////////////////////////////////////////

// compilation safegaurds
#ifndef ICT_ERROR_H_
#define ICT_ERROR_H_
#include <iostream>
namespace ict {
   class Error {
	   char* m_message;
   public:
	  
   // constructors
	  Error(); //Sets the m_message member variable to nullptr.
	  Error(const char*); //Sets the m_message member variable to nullptr and then uses the message() setter member function to set the error message to the errorMessage argument.
	  
   // destructor
	  virtual ~Error(); //de-allocates the memory pointed by m_message.

   // deleted constructor and operator=
	  Error(const Error& em) = delete; //A deleted copy constructor to prevent an Error object to be copied.
	  Error& operator=(const Error& em) = delete; //A deleted assignment operator overload to prevent an Error object to be assigned to another.

   // operator= for c-style strings
	  void operator=(const char* errorMessage); //Sets the m_message to the errorMessage argument and returns nothing.

   // methods
	  void clear(); //de-allocates the memory pointed by m_message and then sets m_message to nullptr. 
	  bool isClear()const; //returns true if m_message is nullptr. 
	  void message(const char* value); //Sets the m_message of the Error object to a new value

   // cast overloads
	  operator const char*() const; //returns the address kept in m_message.
	  operator bool() const; //Exactly like isClear(); returns true if m_message is nullptr

   };
   // operator << overload prototype for cout
   std::ostream& operator<<(std::ostream&, const Error&);
}
#endif

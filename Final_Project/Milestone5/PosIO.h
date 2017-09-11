// Student  Nahal Esmaeili
/////////////////////////////////////////////////////////////////

#ifndef ICT_POSIO_H__
#define ICT_POSIO_H__
// includes go here
#include <iostream>
#include <fstream>
// ict namespace
namespace ict {
	class PosIO {
	public:
		// pure virutal methods go here
		virtual std::fstream& save(std::fstream&)const = 0;
		virtual std::fstream& load(std::fstream&) = 0;
		virtual std::ostream& write(std::ostream&, bool)const = 0;
		virtual std::istream& read(std::istream&) = 0;
	};
}
#endif
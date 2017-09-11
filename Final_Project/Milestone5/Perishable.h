// Student  Nahal Esmaeili
/////////////////////////////////////////////////////////////////

#ifndef ICT_PERISHABLE_H__
#define ICT_PERISHABLE_H__
#include "Date.h"
#include "NonPerishable.h"

namespace ict {
	class Perishable : public NonPerishable
	{
	private:
		Date m_expiry;
		Error m_err;
	protected:
		char signature()const;
	public:
		Perishable();
		const Date& expiry()const;
		void expiry(const Date&);
		std::fstream& save(std::fstream&)const;
		std::fstream& load(std::fstream&);
		std::ostream& write(std::ostream&, bool)const;
		std::istream& read(std::istream&);
	};
}
#endif

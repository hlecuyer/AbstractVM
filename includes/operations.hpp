#ifndef OPERATIONS_HPP
# define OPERATIONS_HPP

#include <typeinfo>

template <typename D, typename U>
std::string		addOperation(D down, U up)
{
	U	toCast;

	try
	{
		toCast = dynamic_cast<U>(D);
	}
	catch (std::bad_cast & e)
	{
		std::cout << "BAD CAST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << std::endl;
	}
}
#endif // ** OPERATIONS_HPP ** //

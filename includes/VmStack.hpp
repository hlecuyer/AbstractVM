// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   mutantstack.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hlecuyer <hlecuyer@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/15 20:11:39 by hlecuyer          #+#    #+#             //
//   Updated: 2015/01/15 22:05:34 by hlecuyer         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //


#ifndef VMSTACK_HPP
#define VMSTACK_HPP

#include <stack>

template <typename T>
class VmStack : public std::stack<T>
{
	private:
		typedef std::stack<T> base;

	public:
	VmStack(void) {}
	~VmStack(void) {}
	VmStack(VmStack const & o): base(o) {}

	typedef typename base::container_type::iterator	iterator;
	using			base::operator=;
	iterator		begin() { return base::c.begin(); }
	iterator		end() { return base::c.end() ; }

};


#endif // ** VMSTACK ** //

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

#include <stack>

#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP


template <typename T>
class MutantStack : public std::stack<T>
{
	private:
		typedef std::stack<T> base;

	public:
	MutantStack(void) {}
		~MutantStack(void) {}
	MutantStack(MutantStack const & o): base(o) {}

	typedef typename base::container_type::iterator	iterator;
	using			base::operator=;
	iterator		begin() { return base::c.begin(); }
	iterator		end() { return base::c.end() ; }

};


#endif

// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hlecuyer <hlecuyer@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/02/10 12:25:28 by hlecuyer          #+#    #+#             //
//   Updated: 2015/02/10 12:25:30 by hlecuyer         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <fstream>
#include <vector>
#include <map >

enum class precision { 
     int8,
     int16,
     int32,
     floatt,
     doublee
};



int main(int argc, char const *argv[])
{
    std::map<std::string, precision> first;

    first["int8"] = precision::int8;
    first["int16"] = precision::int16;
    first["int32"] = precision::int32;


    precision  p =  first["int8"];
    std::cout << static_cast<int>(p) << std::endl;

    p =  first["int32"];
    std::cout << static_cast<int>(p) << std::endl;

    p =  first["int16"];
    std::cout << static_cast<int>(p) << std::endl;

}
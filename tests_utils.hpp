#ifndef TESTS_UTILS_HPP
#define TESTS_UTILS_HPP

#include "inc/map.hpp"
#include <map>
#include <list>
#include <ctime>
#include <iostream>


#define T1 int
#define T2 int
#define T4 int

#define _ft_pair ft::pair
#define _std_pair std::pair

#define _ft ft::map
#define _std std::map

#define _ft_it _ft<T1, T2>::iterator
#define _ft_rit _ft<T1, T2>::reverse_iterator
#define _std_it _std<T1, T2>::iterator
#define _std_rit _std<T1, T2>::reverse_iterator

typedef _ft_pair<T1, T2> FT3;
typedef _std_pair<T1, T2> STD3;

void tests_map();

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
    o << "key: " << iterator->first << " | value: " << iterator->second;
    if (nl)
        o << std::endl;
    return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
    std::cout << "size: " << mp.size() << std::endl;
    std::cout << "max_size: " << mp.max_size() << std::endl;
    if (print_content)
    {
        typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
        std::cout << std::endl << "Content is:" << std::endl;
        for (; it != ite; ++it)
            std::cout << "- " << printPair(it, false) << std::endl;
    }
    std::cout << "---------------------------" << std::endl;
}

template <typename FT_MAP, typename STD_MAP>
void controlSize (FT_MAP my_map, STD_MAP std_map)
{
    std::string toPrint;

    toPrint = (my_map.size() != std_map.size() ? "Size : ❌" : "Size : ✅");
    std::cout << toPrint << std::endl;
}

#endif // TESTS_UTILS_HPP
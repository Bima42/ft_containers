#ifndef TESTS_UTILS_HPP
#define TESTS_UTILS_HPP

#include "map.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "../colors.hpp"
//----------------------------
#include <map>
#include <vector>
#include <stack>
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

#define _fvec ft::vector
#define _svec std::vector

#define _fstack ft::stack
#define _sstack std::stack

#define _pair ft::pair

#define _ft_it _ft<T1, T2>::iterator
#define _ft_rit _ft<T1, T2>::reverse_iterator
#define _std_it _std<T1, T2>::iterator
#define _std_rit _std<T1, T2>::reverse_iterator

typedef _ft_pair<T1, T2> FT3;
typedef _std_pair<T1, T2> STD3;

void tests_map();
void tests_vector();
void tests_stack();

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
    o << "key: " << iterator->first << " | value: " << iterator->second;
    if (nl)
        o << std::endl;
    return ("");
}

template <typename T_MAP>
void	printSizeMap(T_MAP const &mp, bool print_content = 1)
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


template <typename T_VECT>
void    printSize(T_VECT const &vect, bool print_content = 1)
{
    std::cout << "size: " << vect.size() << " // capacity: " << vect.capacity() << std::endl;
    if (print_content)
    {
        typename T_VECT::const_iterator it = vect.begin(), ite = vect.end();
        std::cout << "Content is:" << std::endl;
        for (; it != ite; ++it)
            std::cout << "- " << *it << std::endl;
    }
}

template <typename FT_VECT, typename STD_VECT>
void controlSizeVec (FT_VECT my_vec, STD_VECT std_vec)
{
    std::string toPrint;

    toPrint = (my_vec.size() != std_vec.size() ? "Size : KO" : "Size : OK");
    std::cout << toPrint << std::endl;

    toPrint = (my_vec.capacity() != std_vec.capacity() ? "Capacity : KO" : "Capacity : OK");
    std::cout << toPrint << std::endl;
}

template <typename FT_VECT, typename STD_VECT>
void controlContent (FT_VECT my_vec, STD_VECT std_vec)
{
    std::string toPrint = "Vectors content: ";

    typename STD_VECT::const_iterator it = std_vec.begin(), ite = std_vec.end();
    typename FT_VECT::const_iterator it_ft = my_vec.begin();
    typename FT_VECT::const_iterator it2 = my_vec.begin(), ite2 = my_vec.end();
    typename STD_VECT::const_iterator it_std = std_vec.begin();
    for (; it != ite; ++it){
        if (*it != *it_ft++) {
            toPrint += "❌";
            std::cout << toPrint << std::endl;
            return;
        }
    }
    for (; it2 != ite2; ++it2){
        if (*it2 != *it_std++) {
            toPrint += "❌";
            std::cout << toPrint << std::endl;
            return;
        }
    }
    toPrint += "✅";
    std::cout << toPrint << std::endl;
}

template <class T, class Alloc>
void    cmp(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
{
    static int i = 0;

    std::cout << "############### [" << i++ << "] ###############"  << std::endl;
    std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
    std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
    std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

/*
float	ft_round(double var)
{
    float value = (int)(var * 100000 + .5);
    return((float)value);
}
*/

#endif // TESTS_UTILS_HPP
#ifndef UTILS_HPP
#define UTILS_HPP

#include "iterator_traits.hpp"

namespace ft {
    template <class InputIterator>
    typename ft::iterator_traits<InputIterator>::difference_type distance (InputIterator first, InputIterator last)
    {
        typename ft::iterator_traits<InputIterator>::difference_type ret = 0;
        while (first != last)
        {
            first++;
            ret++;
        }
        return (ret);
    }
}
#endif // UTILS_HPP

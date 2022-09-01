#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>

namespace ft {

    template <class Category, typename T>
    class iterator {
    public:
        typedef T               value_type;
        typedef std::ptrdiff_t  difference_type;
        typedef T&              reference;
        typedef T*              pointer;
        typedef Category        iterator_category;
    };

    class random_access_iterator_tag { };

    class bidirectional_iterator_tag { };

}

#endif //ITERATOR_HPP

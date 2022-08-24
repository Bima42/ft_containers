#ifndef ITERATOR_HPP
#define ITERATOR_HPP

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
}

#endif //FT_CONTAINERS_ITERATOR_HPP

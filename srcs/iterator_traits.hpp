#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

//include <random_access_iterator> cause this file doesnt know random_access_iterator

namespace ft {

    /*
     * Iterator traits class defining properties of iterators.
     * iterator_traits obtains information from Iterator class in template argument.
     * Each trait come from Iterator class in this case.
     */

    template <typename Iterator>
    class iterator_traits {
    public:
        typedef typename Iterator::iterator_category    iterator_category;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
    };

    /*
     * This creates a default operation with an object
     */

    template <typename T>
    class iterator_traits<T*> {
    public:
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef ptrdiff_t                   difference_type;
        typedef T*                          pointer;
        typedef T&                          reference;
    };

    /*
     * This creates a default operation with a const object
     */

    template <typename T>
    class iterator_traits<const T*> {
    public:
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef ptrdiff_t                   difference_type;
        typedef const T*                    pointer;
        typedef const T&                    reference;
    };
}

/*
 * ptrdiff_t :          result of substracting one iterator from another
 * T :                  type of the element where iterator point
 * T* :                 type of pointer to an element where the iterator point
 * T& :                 type of reference where iterator point
 * iterator_category :  iterator category from Iterator
 */

#endif //FT_CONTAINERS_ITERATOR_TRAITS_HPP

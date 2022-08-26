#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace ft {

    template<typename T, typename Alloc = std::allocator<T> >
    class vector
    {
        typedef T                       value_type;
        typedef Alloc                   allocator_type;
        typedef value_type&             reference;
        typedef const value_type&       const_reference;
        typedef value_type*             pointer;
        typedef const value_type*       const_pointer;
        typedef std::ptrdiff_t          difference_type;
        typedef size_t                  size_type;

        /*
         * value_type       : type of the element(s) the vector will hold
         * allocator_type   : allocator type the vector will use
         * reference        : the reference to an element stored in the vector
         * const reference  : the const reference to an element stored in the vector
         * pointer          : gives a pointer to an element stored
         * const_pointer    : gives a const pointer to an element stored
         * difference_type  : can be described as te number of element between two pointers.
         * size_type        : an unsigned integral type that can represent any non-neg. value
         */
    };

}

#endif // VECTOR_HPP
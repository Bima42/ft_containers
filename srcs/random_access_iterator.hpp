#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator.hpp"

namespace ft {

    template <typename T>
    class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T> {

        public:
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type        value_type;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type   difference_type;
            typedef T*  pointer;
            typedef T&  reference;

        private:
            pointer _ptr; // Element pointed by the iterator

        public:
            /* Default constructor, pointer is NULL */
            random_access_iterator() : _ptr(NULL) {}

            /* Constructor from pointer, _ptr point on the element passed as parameter */
            random_access_iterator(pointer ptr) : _ptr(ptr) {}

            /* Copy constructor : construct iterator and copy the pointer */
            random_access_iterator(const random_access_iterator &cpy) : _ptr(cpy._ptr) {}

            /*
             * Copy assignation, give a iterator who is a copy from "rhs"
             * Return the iterator
             */
            random_access_iterator &operator=(const random_access_iterator &rhs)
            {
                if (this == &rhs)
                    return (*this);
                this->_ptr = rhs._ptr;
                return (*this);
            }

            /* Destructor */
            virtual ~random_access_iterator() {}

            /*
             * MEMBER FUNCTIONS, OPERATOR
             */

            /* Base : Give pointer where iterator point, return iterator */
            pointer base() const
            {
                return (this->_ptr);
            }

            /* Operator* : dereference -> give reference to value of element where iterator point*/
            reference operator*() const
            {
                return (*_ptr);
            }

            /* Operator-> : Returns a pointer to the element pointed to by the iterator
             * function calls operator* and returns its address
             */
            pointer operator->() const
            {
                return (&(this->operator*()));
            }

            /* Operator--
             * Predecrement : decrements the base iterator kept by the object, iterator point to the previous element
             * Return : reference
             */
            random_access_iterator &operator--()
            {
                _ptr--;
                return (*this);
            }
            /* Postdecrement : decrement iterator to points to the previous element
             * Return : iterator decremented
             */
            random_access_iterator operator--(int) {
                random_access_iterator tmp = *this;
                --(*this);
                return (tmp);
            }

            /* Operator++
             * * Preincrement : increments the base iterator kept by the object, iterator point to the next element
             * * Return : reference
             * */
            random_access_iterator &operator++()
            {
                _ptr++;
                return (*this);
            }
            /* Postincrement : increment iterator to points to the next element
             * * Return : iterator incremented
             * */
            random_access_iterator operator++(int) {
                random_access_iterator tmp = *this;
                ++(*this);
                return (tmp);
            }

            /* Operator- : give an iterator where element is pointed at "- n" elements
             * Return : iterator pointing to the element located n positions before the element the iterator
             * points to.
             */
            random_access_iterator operator-(difference_type n) const
            {
                return (this->_ptr - n);
            }

            /* Operator+ : give an iterator where element is pointed at "+ n" elements
             * Return : iterator pointing to the element located n positions after the element the iterator
             * points to.
             */
            random_access_iterator operator+(difference_type n) const
            {
                return (this->_ptr + n);
            }

            /* Operator-= : take the element pointed by iterator "- n"
             * Return : reference to iterator
             */
            random_access_iterator &operator-=(difference_type n) const
            {
                this->_ptr -= n;
                return (*this);
            }

            /* Operator+= : take the element pointed by iterator "+ n"
             * Return : reference to iterator
             */
            random_access_iterator &operator+=(difference_type n) const
            {
                this->_ptr += n;
                return (*this);
            }



    };
}

#endif // RANDOM_ACCESS_ITERATOR_HPP
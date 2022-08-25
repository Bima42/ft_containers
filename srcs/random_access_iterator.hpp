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
             * Copy assignation, give an iterator who is a copy from "rhs"
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

            /* Operator [] : Accesses the element located n positions away
             * from the element currently pointed to by the iterator
             */
            reference operator[](difference_type n)
            {
                return (*(operator+(n)));
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

            /* Transform iterator to const iterator */
            operator random_access_iterator<const T> () const
            {
                return (random_access_iterator<const T>(this->_ptr));
            }
    };

    /*
     * Operator== : comparison between two iterators
     * Return : true if equal
     *
     * (1) : both of them are same type (const or not)
     * (2) : in case of const - not const
     */
    /* (1) */
    template<typename T>
    typename ft::random_access_iterator<T>::difference_type operator==(
            const ft::random_access_iterator<T> lhs,
            const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() == rhs.base());
    }
    /* (2) */
    template<typename T1, typename T2>
    typename ft::random_access_iterator<T1>::difference_type operator==(
            const ft::random_access_iterator<T1> lhs,
            const ft::random_access_iterator<T2> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    /*
     * Operator!= : comparison between two iterators
     * Return : true if lhs != rhs
     */
    /* (1) */
    template<typename T>
    typename ft::random_access_iterator<T>::difference_type operator!=(
            const ft::random_access_iterator<T> lhs,
            const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() != rhs.base());
    }
    /* (2) */
    template<typename T1, typename T2>
    typename ft::random_access_iterator<T1>::difference_type operator!=(
            const ft::random_access_iterator<T1> lhs,
            const ft::random_access_iterator<T2> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    /*
     * Operator>= : comparison between two iterators
     * Return : true if lhs >= rhs
     */
    /* (1) */
    template<typename T>
    typename ft::random_access_iterator<T>::difference_type operator>=(
            const ft::random_access_iterator<T> lhs,
            const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() >= rhs.base());
    }
    /* (2) */
    template<typename T1, typename T2>
    typename ft::random_access_iterator<T1>::difference_type operator>=(
            const ft::random_access_iterator<T1> lhs,
            const ft::random_access_iterator<T2> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    /*
     * Operator>= : comparison between two iterators
     * Return : true if lhs <= rhs
     */
    /* (1) */
    template<typename T>
    typename ft::random_access_iterator<T>::difference_type operator<=(
            const ft::random_access_iterator<T> lhs,
            const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() <= rhs.base());
    }
    /* (2) */
    template<typename T1, typename T2>
    typename ft::random_access_iterator<T1>::difference_type operator<=(
            const ft::random_access_iterator<T1> lhs,
            const ft::random_access_iterator<T2> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    /*
     * Operator> : comparison between two iterators
     * Return : true if lhs > rhs
     */
    /* (1) */
    template<typename T>
    typename ft::random_access_iterator<T>::difference_type operator>(
            const ft::random_access_iterator<T> lhs,
            const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() > rhs.base());
    }
    /* (2) */
    template<typename T1, typename T2>
    typename ft::random_access_iterator<T1>::difference_type operator>(
            const ft::random_access_iterator<T1> lhs,
            const ft::random_access_iterator<T2> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    /*
     * Operator< : comparison between two iterators
     * Return : true if lhs < rhs
     */
    /* (1) */
    template<typename T>
    typename ft::random_access_iterator<T>::difference_type operator<(
            const ft::random_access_iterator<T> lhs,
            const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() < rhs.base());
    }
    /* (2) */
    template<typename T1, typename T2>
    typename ft::random_access_iterator<T1>::difference_type operator<(
            const ft::random_access_iterator<T1> lhs,
            const ft::random_access_iterator<T2> rhs)
    {
        return (lhs.base() < rhs.base());
    }


    /*
     * Operator- : Difference between two iterators
     * Return : difference_type
     */
    /* (1) */
    template<typename T>
    typename ft::random_access_iterator<T>::difference_type operator-(
            const ft::random_access_iterator<T> lhs,
            const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() - rhs.base());
    }
    /* (2) */
    template<typename T1, typename T2>
    typename ft::random_access_iterator<T1>::difference_type operator-(
            const ft::random_access_iterator<T1> lhs,
            const ft::random_access_iterator<T2> rhs)
    {
        return (lhs.base() - rhs.base());
    }

    /*
     * Operator+ : return an iterator pointing to "current + n"
     * Return : iterator
     * DISCLAIMER : it's not allowed to
     *      const_iter + const_iter
     *      iter + iter
     *      iter + const_iter
     */
    template<typename T>
    typename ft::random_access_iterator<T> operator+ (
            typename ft::random_access_iterator<T>::difference_type n,
            typename ft::random_access_iterator<T> &current)
    {
        return (&(*current) + n);
    }
}

#endif // RANDOM_ACCESS_ITERATOR_HPP
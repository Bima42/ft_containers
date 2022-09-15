#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator.hpp"
#include "iterator_traits.hpp"

namespace ft {

    template <class Iterator>
    class reverse_iterator {
        public:
            typedef Iterator iterator_type;
            typedef typename ft::iterator_traits<Iterator>::iterator_category   iterator_category;
            typedef typename ft::iterator_traits<Iterator>::value_type          value_type;
            typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;
            typedef typename ft::iterator_traits<Iterator>::pointer             pointer;
            typedef typename ft::iterator_traits<Iterator>::reference           reference;

        private:
            iterator_type _it;

        public:
            reverse_iterator() : _it() {}

            /* Construct from an original iterator type || Replicate the original but iterate in a reverse way
             * explicit to avoid implicit conversion
             */
            explicit reverse_iterator(iterator_type it) : _it(it) {}

            /* Copy construction : Save the sense of rev_it */
            template <class Iter>
            reverse_iterator (const reverse_iterator<Iter> &rev_it) : _it(rev_it.base()) {}

            virtual ~reverse_iterator() {}

            iterator_type base() const
            {
                return (_it);
            }

            /* Operator* : decrease copy of iterator
             * Return : reference to this temp iterator
             */
            reference operator*() const
            {
                iterator_type temp = _it;
                return (*(--temp));
            }

            /* Operator-> : function calls operator* and returns its address
             * Return : pointer to the element pointed to by the iterator
             */
            pointer operator->() const
            {
                return &(operator*());
            }

            /* Operator[] : Accesses the element located n positions away
             * from the element currently pointed to by the iterator
             */
            reference operator[] (difference_type n) const
            {
                return (this->base()[-n - 1]);
            }

            /* Operator-- : decrements the base iterator kept by the object
             * Predecrement :  Return reference
             * Post decrement : Return iterator decremented
             */
            reverse_iterator &operator--()
            {
                ++_it;
                return (*this);
            }

            reverse_iterator operator--(int)
            {
                reverse_iterator temp = *this;
                ++_it;
                return (temp);
            }

             /* Operator++ : increments the base iterator kept by the object
              * Preincrement :  Return reference
              * Postincrement : Return iterator incremented
              */
             reverse_iterator &operator++()
             {
                 --_it;
                 return (*this);
             }

             reverse_iterator operator++(int)
             {
                 reverse_iterator temp = *this;
                 --_it;
                 return (temp);
             }

             /* Operator- : applies the binary operator+ on the base iterator
              * Return : reverse iterator pointing to the element located n positions
              * after the element the iterator currently points to, constructed with the resulting iterator value
              */
             reverse_iterator operator- (difference_type n) const
             {
                return (reverse_iterator(_it + n));
             }

              /* Operator+ : applies the binary operator - on the base iterator
               * Return : reverse iterator pointing to the element located n positions
               * before the element the iterator currently points to, constructed with the resulting iterator value
               */
              reverse_iterator operator+ (difference_type n) const
              {
                  return (reverse_iterator(_it - n));
              }

              /* Operator -= : Decrease the reverse_iterator by n element positions.
               * Decrease by n the base iterator kept by the object (as if applying operator+= to it)
               * Return : incremented iterator
               */
              reverse_iterator &operator-= (difference_type n)
              {
                  this->_it += n;
                  return (*this);
              }

              /* Operator += : Increase the reverse_iterator by n element positions.
              * Increase by n the base iterator kept by the object (as if applying operator-= to it)
              * Return : decremented iterator
              */
              reverse_iterator &operator+= (difference_type n){
                  this->_it -= n;
                  return (*this);
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
    template<typename Iterator>
    bool operator==(
            const ft::reverse_iterator<Iterator> &lhs,
            const ft::reverse_iterator<Iterator> &rhs)
    {
        return (lhs.base() == rhs.base());
    }
    /* (2) */
    template<typename Iter1, typename Iter2>
    bool operator==(
            const ft::reverse_iterator<Iter1> &lhs,
            const ft::reverse_iterator<Iter2> &rhs)
    {
        return (lhs.base() == rhs.base());
    }

    /*
     * Operator!= : comparison between two iterators
     * Return : true if lhs != rhs
     */
    /* (1) */
    template<typename Iterator>
    bool operator!=(
            const ft::reverse_iterator<Iterator> &lhs,
            const ft::reverse_iterator<Iterator> &rhs)
    {
        return (lhs.base() != rhs.base());
    }
    /* (2) */
    template<typename Iter1, typename Iter2>
    bool operator!=(
            const ft::reverse_iterator<Iter1> &lhs,
            const ft::reverse_iterator<Iter2> &rhs)
    {
        return (lhs.base() != rhs.base());
    }

    /*
     * Operator>= : comparison between two iterators
     * Return : true if lhs >= rhs
     */
    /* (1) */
    template<typename Iterator>
    bool operator>=(
            const ft::reverse_iterator<Iterator> &lhs,
            const ft::reverse_iterator<Iterator> &rhs)
    {
        return (lhs.base() <= rhs.base());
    }
    /* (2) */
    template<typename Iter1, typename Iter2>
    bool operator>=(
            const ft::reverse_iterator<Iter1> &lhs,
            const ft::reverse_iterator<Iter2> &rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    /*
     * Operator>= : comparison between two iterators
     * Return : true if lhs <= rhs
     */
    /* (1) */
    template<typename Iterator>
    bool operator<=(
            const ft::reverse_iterator<Iterator> &lhs,
            const ft::reverse_iterator<Iterator> &rhs)
    {
        return (lhs.base() >= rhs.base());
    }
    /* (2) */
    template<typename Iter1, typename Iter2>
    bool operator<=(
            const ft::reverse_iterator<Iter1> &lhs,
            const ft::reverse_iterator<Iter2> &rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    /*
     * Operator> : comparison between two iterators
     * Return : true if lhs > rhs
     */
    /* (1) */
    template<typename Iterator>
    bool operator>(
            const ft::reverse_iterator<Iterator> &lhs,
            const ft::reverse_iterator<Iterator> &rhs)
    {
        return (lhs.base() < rhs.base());
    }
    /* (2) */
    template<typename Iter1, typename Iter2>
    bool operator>(
            const ft::reverse_iterator<Iter1> &lhs,
            const ft::reverse_iterator<Iter2> &rhs)
    {
        return (lhs.base() < rhs.base());
    }

    /*
     * Operator< : comparison between two iterators
     * Return : true if lhs < rhs
     */
    /* (1) */
    template<typename Iter>
    bool operator<(
            const ft::reverse_iterator<Iter> &lhs,
            const ft::reverse_iterator<Iter> &rhs)
    {
        return (lhs.base() > rhs.base());
    }
    /* (2) */
    template<typename Iter1, typename Iter2>
    bool operator<(
            const ft::reverse_iterator<Iter1> &lhs,
            const ft::reverse_iterator<Iter2> &rhs)
    {
        return (lhs.base() > rhs.base());
    }


    /*
     * Operator- : Difference between two iterators
     * Return : difference_type (number of elements)
     */
    /* (1) */
    template<typename Iterator>
    typename ft::reverse_iterator<Iterator>::difference_type operator-(
            const ft::reverse_iterator<Iterator> &lhs,
            const ft::reverse_iterator<Iterator> &rhs)
    {
        return (rhs.base() - lhs.base());
    }
    /* (2) */
    template<typename Iter1, typename Iter2>
    typename ft::reverse_iterator<Iter1>::difference_type operator-(
            const ft::reverse_iterator<Iter1> &lhs,
            const ft::reverse_iterator<Iter2> &rhs)
    {
        return (rhs.base() - lhs.base());
    }

    /*
     * Operator+ : return an iterator pointing to "current + n"
     * Return : reverse iterator
     */
    template<typename Iterator>
    typename ft::reverse_iterator<Iterator> operator+ (
            typename ft::reverse_iterator<Iterator>::difference_type n,
            typename ft::reverse_iterator<Iterator> &current)
    {
        return (current + n);
    }
}

#endif // REVERSE_ITERATOR_HPP

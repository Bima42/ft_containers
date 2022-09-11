#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {
    template <class T1, class T2>
    struct pair
    {
        /*
         * first_type is the first bound type
         * second_type is the second bound type
         */
        typedef T1 first_type;
        typedef T2 second_type;

        /*
         * first is a copy of the first object
         * second is a copy of the second object
         */
        first_type  first;
        second_type second;

        /* Default constructor creates first and second using their respective default constructors */
        pair() : first(), second() {}

        /* Two objects may be passed to a pair constructor to be copied */
        pair(const first_type &a, const second_type &b) : first(a), second(b) {}

        /* There is also a templated copy constructor for the pair class itself. */
        template <class U1, class U2>
        pair (const pair<U1, U2> &p) : first(p.first), second(p.second) {}

        pair &operator=(const pair &p)
        {
            if (this == &p)
                return (*this);
            first = p.first;
            second = p.second;
            return (*this);
        }
    };

    template <class T1, class T2>
    bool operator== (const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
    {
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }

    template <class T1, class T2>
    bool operator< (const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
    {
        return (lhs.first < rhs.first
            || (lhs.first <= rhs.first && lhs.second < rhs.second));
    }

    template <class T1, class T2>
    bool operator!= (const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
    {
        return (!(lhs == rhs));
    }

    template <class T1, class T2>
    bool operator> (const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
    {
        return (rhs < lhs);
    }

    template <class T1, class T2>
    bool operator>= (const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
    {
        return (!(lhs < rhs));
    }

    template <class T1, class T2>
    bool operator<= (const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
    {
        return (!(rhs < lhs));
    }

    /*
     * Function Make_pair
     */
    template <class T1, class T2>
    ft::pair<T1, T2> make_pair(T1 lhs, T2 rhs)
    {
        return (ft::pair<T1, T2>(lhs, rhs));
    }
}

#endif // PAIR_HPP
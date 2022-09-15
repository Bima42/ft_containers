#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {

    template <class T, class Container = ft::vector<T> >
    class stack {

        public:
            typedef Container   container_type;
            typedef T           value_type;
            typedef size_t      size_type;

        protected:
            container_type c;

        public:
            explicit stack( const Container &cont = Container() ) : c(cont) {}
            stack( const stack &x ) { *this = x; }
            ~stack() {}

            stack &operator=(const stack &x)
            {
                if (this != &x)
                    this->c = x.c;
                return (*this);
            }

            bool empty() const { return (c.empty()); }

            void push (const value_type& val) { c.push_back(val); }
            void pop() { c.pop_back(); }

            size_type size() const { return (c.size()); }

            value_type &top() { return (c.back()); }
            const value_type &top() const { return (c.back()); }

            /*
             * Need to declare those prototypes, using key word friend, to give access to private attributes
             */
            template <class Type, class Cont>
            friend bool operator== (const stack<Type,Cont> &lhs, const stack<Type,Cont> &rhs);

            template <class Type, class Cont>
            friend bool operator!= (const stack<Type,Cont> &lhs, const stack<Type,Cont> &rhs);

            template <class Type, class Cont>
            friend bool operator<  (const stack<Type,Cont> &lhs, const stack<Type,Cont> &rhs);

            template <class Type, class Cont>
            friend bool operator<= (const stack<Type,Cont> &lhs, const stack<Type,Cont> &rhs);

            template <class Type, class Cont>
            friend bool operator>  (const stack<Type,Cont> &lhs, const stack<Type,Cont> &rhs);

            template <class Type, class Cont>
            friend bool operator>= (const stack<Type,Cont> &lhs, const stack<Type,Cont> &rhs);
    };

    template <class T, class Container>
    bool operator== (const stack<T,Container> &lhs, const stack<T,Container> &rhs)
    {
        return (lhs.c == rhs.c);
    }

    template <class T, class Container>
    bool operator!= (const stack<T,Container> &lhs, const stack<T,Container> &rhs)
    {
        return (lhs.c != rhs.c);
    }

    template <class T, class Container>
    bool operator<  (const stack<T,Container> &lhs, const stack<T,Container> &rhs)
    {
        return (lhs.c < rhs.c);
    }

    template <class T, class Container>
    bool operator<= (const stack<T,Container> &lhs, const stack<T,Container> &rhs)
    {
        return (lhs.c <= rhs.c);
    }

    template <class T, class Container>
    bool operator>  (const stack<T,Container> &lhs, const stack<T,Container> &rhs)
    {
        return (lhs.c > rhs.c);
    }

    template <class T, class Container>
    bool operator>= (const stack<T,Container> &lhs, const stack<T,Container> &rhs)
    {
        return (lhs.c >= rhs.c);
    }
}

#endif // STACK_HPP

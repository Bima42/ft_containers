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

        private:
            container_type _container;

        public:
            explicit stack( const Container &cont = Container() ) : _container(cont) {}
            stack( const stack &x ) { *this = x; }
            ~stack() {}

            stack &operator=(const stack &x)
            {
                if (this != &x)
                    this->_container = x._container;
                return (*this);
            }

            bool empty() const { return (_container.empty()); }

            void push (const value_type& val) { _container.push_back(val); }
            void pop() { _container.pop_back(); }

            size_type size() const { return (_container.size()); }

            value_type &top() { return (_container.back()); }
            const value_type &top() const { return (_container.back()); }

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
        return (lhs._container == rhs._container);
    }

    template <class T, class Container>
    bool operator!= (const stack<T,Container> &lhs, const stack<T,Container> &rhs)
    {
        return (lhs._container != rhs._container);
    }

    template <class T, class Container>
    bool operator<  (const stack<T,Container> &lhs, const stack<T,Container> &rhs)
    {
        return (lhs._container < rhs._container);
    }

    template <class T, class Container>
    bool operator<= (const stack<T,Container> &lhs, const stack<T,Container> &rhs)
    {
        return (lhs._container <= rhs._container);
    }

    template <class T, class Container>
    bool operator>  (const stack<T,Container> &lhs, const stack<T,Container> &rhs)
    {
        return (lhs._container > rhs._container);
    }

    template <class T, class Container>
    bool operator>= (const stack<T,Container> &lhs, const stack<T,Container> &rhs)
    {
        return (lhs._container >= rhs._container);
    }
}

#endif // STACK_HPP
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "is_integral.hpp"
#include "enable_if.hpp"
#include "utils.hpp"

namespace ft {

    template<typename T, typename Alloc = std::allocator<T> >
    class vector
    {
        public :
            typedef T                                               value_type;
            typedef Alloc                                           allocator_type;
            typedef typename allocator_type::reference              reference;
            typedef typename allocator_type::const_reference        const_reference;
            typedef typename allocator_type::pointer                pointer;
            typedef typename allocator_type::const_pointer          const_pointer;
            typedef ft::random_access_iterator<value_type>          iterator;
            typedef ft::random_access_iterator<const value_type>    const_iterator;
            typedef ft::reverse_iterator<iterator>                  reverse_iterator;
            typedef ft::reverse_iterator<const iterator>            const_reverse_iterator;
            typedef size_t                                          size_type;
            typedef ft::iterator_traits<iterator>                   difference_type;

        /*
         * value_type               : type of the element(s) the vector will hold
         * allocator_type           : allocator type the vector will use
         * reference                : the reference to an element stored in the vector
         * const reference          : the const reference to an element stored in the vector
         * pointer                  : gives a pointer to an element stored
         * const_pointer            : gives a const pointer to an element stored
         * iterator                 : random_access_iterator to value_type. Read or modify elements. Convertible to const
         * const_iterator           : const random_Access_iterator. Only read elements
         * reverse_iterator         : Reverse of iterator. Read or modify elements in reverse vector.
         * const_reverse_iterator   : Const reverse of iterator. Only read elements
         * difference_type          : can be described as the number of element between two pointers.
         *                          Same as ptrdiff_t. Signed integral type
         * size_type                : an unsigned integral type that can represent any non-neg. value of difference_type
         *                             Same as size_t
         */

        private:
            allocator_type  _alloc;
            pointer         _vector;
            size_type       _size;
            size_type       _capacity;

        public:
            /* Default Constructor : empty container.
             * In template : if second parameter is not defined, std::allocator is used.
             */
            explicit vector (const allocator_type &alloc = allocator_type()) :
                _alloc(alloc), _vector(NULL), _size(0), _capacity(0) {}

            /*
             * Constructor with n elements. Elements are copy of val
             * allocate : allocate a block of storage with a size large enough to contain n elements
             * of member type value_type. Returns a pointer to the first element
             */
            explicit vector (size_type n, const value_type &val = value_type(),
                             const allocator_type &alloc = allocator_type()) :
                             _alloc(alloc), _size(n), _capacity(n)
            {
                _vector = _alloc.allocate(n);
                for (size_type i = 0; i < _size; i++) {
                    _alloc.construct((_vector + i), val);
                }
            }

            /*
             * TODO : NEED PROTECTION HERE ??? We dont put for the moment
             * Constructor using Range : build container using elements in range [first, last)
             *
             * ft::distance(first, last) : number of elements between first and last
             */
            template <class InputIterator>
                    vector ( typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
                             InputIterator last,
                             const allocator_type &alloc = allocator_type() ) : _alloc(alloc)
            {
                    size_type diff = ft::distance(first, last);

                    _vector = _alloc.allocate(diff);
                    _size = diff;
                    _capacity = diff;

                    for (size_t i = 0; i < diff; i++) {
                        _alloc.construct((_vector + i), *first++);
                    }
            }

            /*
             * Copy Constructor
             * Will copy each element of the vector given in parameter
             * TODO : use insert() function to copy the vector ? REMAKE COPY CONSTRUCTOR
             */
            vector (const vector &x) : _alloc(x._alloc), _size(0), _capacity(0), _vector(NULL)
            {
                *this = x;
            }

            /* Destructor */
            ~vector()
            {
                this->clear();
                _alloc.deallocate(_vector, _capacity);
            }

            /* Operator= overload : assign each element of vector given in parameter to the container
             * Replace content and according size
             * Have to clear the content of the previous container
             */
            vector &operator=(const vector &x)
            {
                if (this == &x)
                    return (*this);
                this->clear();
                _vector = _alloc.allocate(_vector, x.capacity());
                for (size_type i = 0; i < x.size(); i++) {
                    _vector[i] = x._vector[i];
                }
                _size = x.size();
                _capacity = x.capacity();
            }


            /* Assign() : Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
             *      - range version : the new contents are elements constructed from each of the elements in the range between first and last, excluding last.
             *      - fill version : the new contents are n elements, each initialized to a copy of val.
             *      - Any elements held in the container before the call are destroyed and replaced by newly constructed elements
             *      : automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
             */
            template <class InputIterator>
            void assign (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
                         InputIterator last)
            {
                size_type diff = ft::distance(first, last);
                this->clear();
                if (diff > this->_capacity)
                {
                    _alloc.deallocate(_vector, _capacity);
                    _vector = _alloc.allocate(diff + 1);
                }
                for (size_type i = 0; first != last; i++) {
                    _alloc.construct((_vector + i), *first++);
                }
                this->_size = diff;
            }

            void assign (size_type n, const value_type& val)
            {
                this->clear();
                if (n > this->_capacity)
                {
                    _alloc.deallocate(_vector, _capacity);
                    _vector = _alloc.allocate(n);
                }
                for (size_type i = 0; i != n; i++) {
                    _alloc.construct((_vector + i), val);
                }
                this->_size = n;
            }

            /*--------------------------ITERATOR--------------------------*/
            /* cbegin, cend, crbegin, crend : Are used in C++11 and plus. We don't implement it */
            iterator begin() { return (iterator(_vector)); }
            const iterator begin() const { return (const_iterator(_vector)); }
            iterator end() { return (iterator(_vector + this->_size)); }
            const iterator end() const { return (const_iterator(_vector + this->_size)); }

            /*-----------------------REVERSE-ITERATOR-----------------------*/
            reverse_iterator rbegin() { return (reverse_iterator(iterator(_vector))); }
            const_reverse_iterator rbegin() const { return (const_reverse_iterator(iterator(_vector))); }
            reverse_iterator rend() { return (reverse_iterator(iterator(_vector + this->_size))); }
            const_reverse_iterator rend() const { return (const_reverse_iterator(iterator(_vector + this->_size))); }


            /*---------------------------CAPACITY-------------------------------*/
            size_type capacity () const { return (this->_capacity); }
            size_type size () const { return (this->_size); }
            size_type max_size() const { return (_alloc.max_size()); }
            bool empty () const { return (this->_size == 0); }

            /* Resize() : Resizes the container so that it contains n elements
             *      - n < _size : the content is reduced to its first n elements, removing those beyond (and destroying them).
             *      - n > _size : the content is expanded by inserting at the end as many elements as needed to reach a size of n.
             *      If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.
             *      - n > capacity : an automatic reallocation of the allocated storage space takes place.
             * This function changes the actual content of the container by inserting or erasing elements from it.
             */
            void resize (size_type n, value_type val = value_type())
            {
                if (n > this->max_size())
                    throw (std::length_error("The requested size is too high"));
                else if (n <= this->_size)
                {
                    for (size_type i = n; i < this->_size; i++) {
                        _alloc.destroy(_vector + i);
                    }
                }
                else if (n > this->_size)
                {
                    pointer tmp = _alloc.allocate(n);

                    for (size_type i = 0; i < this->_size; i++) {
                        _alloc.construct(tmp + i, *(_vector + i));
                    }

                    for (size_type i = this->_size; i < n; i++) {
                        _alloc.construct(tmp + i, val);
                    }

                    this->clear();
                    _alloc.deallocate(this->_vector, this->_capacity);
                    this->_vector = tmp;

                    if (n > this->_capacity * 2)
                        this->_capacity = n;
                    else if (n > this->_capacity)
                        this->_capacity *= 2;
                }
                this->_size = n;
            }

            /* Reserve() : Requests that the vector capacity be at least enough to contain n elements.
             *      - n is greater than the current vector capacity : container reallocate its storage increasing its capacity to n
             *      - All other cases : does not cause a reallocation and the vector capacity is not affected.
             */
            void reserve (size_type n)
            {
                if (n > this->max_size())
                    throw::std::length_error("The requested size is too high");
                if (this->_capacity <= n)
                {
                    pointer tmp = _alloc.allocate(n);
                    for (size_type i = 0; i < this->_size; i++) {
                        _alloc.construct(tmp + i, *(this->_vector + i));
                    }

                    for (size_type i = 0; i < this->_capacity; i++) {
                        _alloc.destroy(_vector + i);
                    }
                    _alloc.deallocate(this->_vector, this->_capacity);

                    this->_vector = tmp;
                    this->_capacity = n;
                }
            }


            /*-----------------------ELEMENT-ACCESS--------------------------*/
            reference front() { return (_vector[0]); }
            const_reference front() const { return (_vector[0]) ;}
            reference back() { return (_vector[_size - 1]); }
            const_reference back() const { return (_vector[_size - 1]); }
            reference operator[] (size_type n) { return (_vector[n]); }
            const_reference operator[] (size_type n) const { return (_vector[n]); }

            /* at() : Returns a reference to the element at position n in the vector
             * Difference with operator[] : throw an exception if the index given as parameter is
             * out of the range of our vector
             */
            reference at (size_type n)
            {
                if (n >= this->_size)
                    throw std::out_of_range("Index used is out of range");
                return (this->_vector[n]);
            }

            const_reference at (size_type n) const
            {
                if (n >= this->_size)
                    throw std::out_of_range("Index used is out of range");
                return (this->_vector[n]);
            }

            /* push_back() : add element at the end after its current last element
             *      - content of val is copied (or moved) to the new element.
             *      - increases the container size by one : causes an automatic reallocation of the allocated storage
             * space if -and only if- the new vector size surpasses the current vector capacity.
             */
            void push_back (const value_type& val)
            {
                // TODO : Ternaire ici non ??
                if (this->_capacity == 0)
                {
                    this->_capacity = 1;
                    this->reserve(this->capacity());
                }
                else if (this->_size + 1 > this->capacity())
                    this->reserve(this->capacity() * 2);
                _alloc.construct((this->_vector + this->size()), val);
                this->_size += 1;
            }

            /* pop_back() : Removes the last element in the vector, effectively reducing the container size by one
             *      - This destroys the removed element.
             */
            void pop_back()
            {
                if (!(this->empty()))
                {
                    _alloc.destroy(&this->back());
                    this->_size--;
                }
            }

            /* TODO : insert()
             *
             */


            /* erase() : Removes from the vector either a single element (position) or a range of elements [first,last]
             *      - reduces the container size by the number of elements removed, which are destroyed.
             *      - Because vectors use an array as their underlying storage, erasing elements in positions other
             *      than the vector end causes the container to relocate all the elements after the segment erased to their new positions
             *      - Return : An iterator pointing to the new location of the element that followed the last element erased by the
             *      function call. (container end if the operation erased the last element in the sequence)
             */
            iterator erase (iterator position)
            {
                _alloc.destroy(&(*position));
                for (iterator it = position; it != this->end(); it++) {
                    *it = *(it + 1);
                }
                this->_size -= 1;
                return (position);
            }

            iterator erase (iterator first, iterator last)
            {
                size_type erase = 0;

                for (iterator it = first; it != last; it++) {
                    _alloc.destroy(&(*it));
                    erase++;
                }
                for (iterator it = first; last != this->end(); last++) {
                    *it = *last;
                    it++;
                }
                this->_size -= erase;
                return (first);
            }

            /* Swap() : Exchanges the content of the container by the content of x, which is another vector object of the same type
             *      - Sizes may differ.
             *      - After call to this function, elements in this container are those which were in x before the call
             *      and the elements of x are those which were in this.
             *      - All iterators, references and pointers remain valid for the swapped objects
             *      - Notice that a non-member function exists with the same name, swap, overloading that algorithm with an optimization that behaves like this member function.
             */
            void swap (vector &x)
            {
                if (this == &x)
                    return ;

                allocator_type  _alloc_tmp = x._alloc;
                pointer         _vector_tmp = x._vector;
                size_type       _size_tmp = x._size;
                size_type       _capacity_tmp = x._capacity;

                x._alloc = this->_alloc;
                x._vector = this->_vector;
                x._size = this->_size;
                x._capacity = this->_capacity;

                this->_alloc = _alloc_tmp;
                this->_vector = _vector_tmp;
                this->_size = _size_tmp;
                this->_capacity = _capacity_tmp;
            }

            /* TODO : shrink to fit */

            /* Clear : destroy all elements using destroy, but NOT DEALLOCATE */
            void clear()
            {
                for (size_type i = 0; i < this->_capacity; i++) {
                    _alloc.destroy(_vector + i);
                }
                this->_size = 0;
            }
    };

    /* TODO : OPERATORS */
}

#endif // VECTOR_HPP
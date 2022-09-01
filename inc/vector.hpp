#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "is_integral.hpp"
#include "enable_if.hpp"
#include "equal.hpp"
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
            typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;
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
            pointer         _vec;
            size_type       _size;
            size_type       _capacity;

        public:
            /* Default Constructor : empty container.
             * In template : if second parameter is not defined, std::allocator is used.
             */
            explicit vector (const allocator_type &alloc = allocator_type()) :
                _alloc(alloc), _vec(NULL), _size(0), _capacity(0) {}

            /*
             * Constructor with n elements. Elements are copy of val
             * allocate : allocate a block of storage with a size large enough to contain n elements
             * of member type value_type. Returns a pointer to the first element
             */
            explicit vector (size_type n, const value_type &val = value_type(),
                             const allocator_type &alloc = allocator_type()) :
                             _alloc(alloc), _vec(NULL), _size(n), _capacity(n)
            {
                _vec = _alloc.allocate(n);
                for (size_type i = 0; i < _size; i++) {
                    _alloc.construct((_vec + i), val);
                }
            }

            /*
             * Constructor using Range : build container using elements in range [first, last)
             * ft::distance(first, last) : number of elements between first and last
             */
            template <class InputIterator>
                    vector ( typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
                             InputIterator last,
                             const allocator_type &alloc = allocator_type() ) : _alloc(alloc)
            {
                    size_type diff = ft::distance(first, last);

                    _vec = _alloc.allocate(diff);
                    _size = diff;
                    _capacity = diff;

                    for (size_t i = 0; i < diff; i++) {
                        _alloc.construct((_vec + i), *first++);
                    }
            }

            /*
             * Copy Constructor
             * Will copy each element of the vector given in parameter
             * TODO : use insert()
             */
            vector (const vector &x) : _alloc(x._alloc), _vec(NULL), _size(0), _capacity(0)
            {
                //this->insert(this->begin(), x.begin(), x.end());
                *this = x;
            }

            /* Destructor */
            virtual ~vector()
            {
                this->clear();
                _alloc.deallocate(_vec, _capacity);
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
                if (this->capacity() < x.capacity())
                    this->reserve(x.capacity());
                for (size_type i = 0; i < x.size(); i++) {
                    _alloc.construct(_vec + i, x._vec[i]);
                }
                _size = x.size();
                _capacity = x.capacity();
                return (*this);
            }


            /*--------------------------ITERATOR--------------------------*/
            /* cbegin, cend, crbegin, crend : Are used in C++11 and plus. We don't implement it */
            iterator begin() { return (iterator(_vec)); }
            const_iterator begin() const { return (const_iterator(_vec)); }
            iterator end() { return (iterator(_vec + this->_size)); }
            const_iterator end() const { return (const_iterator(_vec + this->_size)); }

            /*-----------------------REVERSE-ITERATOR-----------------------*/
            reverse_iterator rbegin() { return (reverse_iterator(iterator(this->end()))); }
            const_reverse_iterator rbegin() const { return (const_reverse_iterator(iterator(this->end()))); }
            reverse_iterator rend() { return (reverse_iterator(iterator(this->begin()))); }
            const_reverse_iterator rend() const { return (const_reverse_iterator(iterator(this->begin()))); }


            /*--------------------------------------------------------------------*
             *                                                                    *
             *                         CAPACITY                                   *
             *                                                                    *
             *--------------------------------------------------------------------*/
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
                        _alloc.destroy(_vec + i);
                    }
                }
                else if (n > this->_size)
                {
                    pointer tmp = _alloc.allocate(n);

                    for (size_type i = 0; i < this->_size; i++) {
                        _alloc.construct(tmp + i, *(_vec + i));
                    }

                    for (size_type i = this->_size; i < n; i++) {
                        _alloc.construct(tmp + i, val);
                    }

                    this->clear();
                    _alloc.deallocate(this->_vec, this->_capacity);
                    this->_vec = tmp;

                    /* Adapt capacity if n > capacity
                     * Otherwise we keep capacity */
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
                        _alloc.construct(tmp + i, *(this->_vec + i));
                    }

                    for (size_type i = 0; i < this->_capacity; i++) {
                        _alloc.destroy(_vec + i);
                    }
                    _alloc.deallocate(this->_vec, this->_capacity);

                    this->_vec = tmp;
                    this->_capacity = n;
                }
            }

            /* Shrink_to_fit : Requests the container to reduce its capacity to fit its size */
            void shrink_to_fit()
            {
                if (this->size() < this->capacity())
                {
                    pointer tmp = _alloc.allocate(this->size());
                    for (size_type i = 0; i < this->size(); i++)
                        _alloc.construct(tmp + i, *(this->_vec + i));

                    for (size_type i = 0; i < this->capacity(); i++)
                        _alloc.destroy(this->_vec + i);
                    _alloc.deallocate(this->_vec, this->capacity());

                    this->_vec = tmp;
                    this->_capacity = this->size();
                }
            }


            /*--------------------------------------------------------------------*
             *                                                                    *
             *                         ELEMENT ACCESS                             *
             *                                                                    *
             *--------------------------------------------------------------------*/
            reference front() { return (_vec[0]); }
            const_reference front() const { return (_vec[0]) ;}
            reference back() { return (_vec[_size - 1]); }
            const_reference back() const { return (_vec[_size - 1]); }
            reference operator[] (size_type n) { return (_vec[n]); }
            const_reference operator[] (size_type n) const { return (_vec[n]); }

            /* at() : Returns a reference to the element at position n in the vector
             * Difference with operator[] : throw an exception if the index given as parameter is
             * out of the range of our vector
             */
            reference at (size_type n)
            {
                if (n >= this->_size)
                    throw std::out_of_range("Index used is out of range");
                return (this->_vec[n]);
            }

            const_reference at (size_type n) const
            {
                if (n >= this->_size)
                    throw std::out_of_range("Index used is out of range");
                return (this->_vec[n]);
            }

            /* data() : Returns a direct pointer to the memory array used internally by the vector to store its owned elements.
             *      - If vector object is const-qualified, the function returns a pointer to const value_type
             */
            value_type *data() { return (this->_vec); }

            const value_type *data() const { return (this->_vec); }


            /*--------------------------------------------------------------------*
             *                                                                    *
             *                         MODIFIERS                                  *
             *                                                                    *
             *--------------------------------------------------------------------*/

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
                    _alloc.deallocate(_vec, _capacity);
                    _vec = _alloc.allocate(diff);
                    this->_capacity = diff;
                }
                for (size_type i = 0; first != last; i++) {
                    _alloc.construct((_vec + i), *first++);
                }
                this->_size = diff;
            }

            void assign (size_type n, const value_type& val)
            {
                this->clear();
                if (n > this->_capacity)
                {
                    _alloc.deallocate(_vec, _capacity);
                    _vec = _alloc.allocate(n);
                    this->_capacity = n;
                }
                for (size_type i = 0; i != n; i++) {
                    _alloc.construct((_vec + i), val);
                }
                this->_size = n;
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
                    this->reserve(1);
                else if (this->_size + 1 > this->capacity())
                    this->reserve(this->capacity() * 2);
                _alloc.construct((this->_vec + this->size()), val);
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

            /* insert() : vector is extended by inserting new elements before the element at the specified position
             *      - increasing the container size by the number of elements inserted.
             *      - causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
             *      Because vectors use an array as their underlying storage : relocate all the elements that were after position to their new positions.
             */
            iterator insert(iterator position, const value_type &val)
            {
                if (this->size() + 1 > this->capacity())
                {
                    if (this->size() == 0)
                    {
                        this->_size = 1;
                        this->_capacity = 1;
                        this->_vec = _alloc.allocate(1);
                        _alloc.construct(this->_vec, val);
                    }
                    else {
                        size_type i = 0;
                        iterator it_tmp = this->begin();
                        size_type ret = position - this->begin();
                        pointer tmp = _alloc.allocate(this->capacity() * 2);
                        _size += 1;
                        for (size_type j = 0; j < this->size(); j++) {
                            if (it_tmp == position)
                                _alloc.construct(tmp + i++, val);
                            _alloc.construct(tmp + i++, *(_vec + j));
                            it_tmp++;
                        }
                        for (size_type j = 0; j < this->size(); j++)
                            _alloc.destroy(_vec + j);
                        _alloc.deallocate(_vec, _capacity);
                        _capacity *= 2;
                        _vec = tmp;
                        return iterator(_vec + ret);
                    }
                } else {
                    _size += 1;
                    for (iterator it = this->end(); it != position; it--) {
                        *it = *(it - 1);
                    }
                    *position = val;
                }
                return (position);
            }

                void insert(iterator position, size_type n, const value_type &val)
            {
                if (_size + n > _capacity)
                {
                    size_type distance = ft::distance(this->begin(), position);

                    if (this->size() + n > this->capacity() * 2)
                        this->_capacity = n + this->size();
                    else if (this->size() + n > this->capacity())
                        this->_capacity *= 2;
                    pointer tmp = _alloc.allocate(this->capacity());
                    for (size_type i = 0; i < distance; i++)
                        _alloc.construct(tmp + i, *(_vec + i));
                    for (size_type i = 0; i < n; i++)
                        _alloc.construct(tmp + i + distance, val);
                    for (size_type i = 0; i < this->size(); i++)
                        _alloc.construct(tmp + distance + n + i, *(_vec + distance + i));
                    _size = this->size() + n;
                    for (size_type j = 0; j < this->size(); j++)
                        _alloc.destroy(_vec + j);
                    _alloc.deallocate(_vec, _capacity);
                    _vec = tmp;
                }
                else
                {
                    size_type new_end = _size + n;
                    for (iterator end_scope = this->end(); end_scope != position; end_scope--)
                    {
                        _alloc.construct(_vec + new_end--, *end_scope);
                    }
                    _alloc.construct(_vec + new_end, *position);
                    for (size_type i = 0;i < n; i++)
                    {
                        *(position + i) = val;
                    }
                    _size += n;
                }
            }

            template <class InputIterator>
            void insert (iterator position,
                         typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
                         InputIterator last)
            {
                size_type n = ft::distance(first, last);
                size_type distance = ft::distance(this->begin(), position);
                if (_size + n > _capacity)
                {
                    //TODO: Protect if 0 !!!!!!
                    if (this->size() + n > this->capacity() * 2)
                        this->_capacity = n + this->size();
                    else if (this->size() + n > this->capacity())
                        this->_capacity *= 2;
                    pointer tmp = _alloc.allocate(this->capacity());
                    for (size_type i = 0; i < distance; i++)
                        _alloc.construct(tmp + i, *(_vec + i));
                    for (size_type i = 0; i < n; i++)
                        _alloc.construct(tmp + i + distance, *first++);
                    for (size_type i = 0; i < this->size(); i++)
                        _alloc.construct(tmp + distance + n + i, *(_vec + distance + i));
                    _size = this->size() + n;
                    for (size_type j = 0; j < this->size(); j++)
                        _alloc.destroy(_vec + j);
                    _alloc.deallocate(_vec, _capacity);
                    _vec = tmp;
                }
                else
                {
                    size_type new_end = _size + n;
                    for (iterator end_scope = this->end(); end_scope != position; end_scope--)
                    {
                        _alloc.construct(_vec + new_end--, *end_scope);
                    }
                    _alloc.construct(_vec + new_end, *position);
                    for (size_type i = 0;i < n; i++)
                    {
                        *(position + i) = *first++;
                    }
                    _size += n;
                }

            }


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
                pointer         _vec_tmp = x._vec;
                size_type       _size_tmp = x._size;
                size_type       _capacity_tmp = x._capacity;

                x._alloc = this->_alloc;
                x._vec = this->_vec;
                x._size = this->_size;
                x._capacity = this->_capacity;

                this->_alloc = _alloc_tmp;
                this->_vec = _vec_tmp;
                this->_size = _size_tmp;
                this->_capacity = _capacity_tmp;
            }

            /* Clear : destroy all elements using destroy, but NOT DEALLOCATE */
            void clear()
            {
                for (size_type i = 0; i < this->_capacity; i++) {
                    _alloc.destroy(_vec + i);
                }
                this->_size = 0;
            }
    };

    template <class T, class Alloc>
    bool operator== (const ft::vector<T,Alloc> &lhs, const ft::vector<T,Alloc> &rhs)
    {
        if (lhs.size() != rhs.size())
            return (false);
        for (size_t i = 0; i < lhs.size(); i++) {
            if (lhs[i] != rhs[i])
                return (false);
        }
        return (true);
    }

    template <class T, class Alloc>
    bool operator!= (const ft::vector<T,Alloc> &lhs, const ft::vector<T,Alloc> &rhs)
    {
        return (!(lhs == rhs));
    }

    template <class T, class Alloc>
    bool operator<  (const ft::vector<T,Alloc> &lhs, const ft::vector<T,Alloc> &rhs)
    {
        typename ft::vector<T>::const_iterator right = rhs.begin();

        for (typename ft::vector<T>::const_iterator left = lhs.begin(); left != lhs.end(); left++) {
            if (right == rhs.end() || *right < *left)
                return (false);
            else if (*left < *right)
                return (true);
            right++;
        }
        return (right != rhs.end());
    }

    template <class T, class Alloc>
    bool operator<= (const ft::vector<T,Alloc> &lhs, const ft::vector<T,Alloc> &rhs)
    {
        return (!(rhs < lhs));
    }

    template <class T, class Alloc>
    bool operator>  (const ft::vector<T,Alloc> &lhs, const ft::vector<T,Alloc> &rhs)
    {
        return (rhs < lhs);
    }

    template <class T, class Alloc>
    bool operator>= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
    {
        return (!(lhs < rhs));
    }

    /* Swap() : overloading swap algorithm with an optimization that behaves like this member function. */
    template <class T, class Alloc>
    void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>&y)
    {
        x.swap(y);
    }
}

#endif // VECTOR_HPP
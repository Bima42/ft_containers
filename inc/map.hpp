#ifndef MAP_HPP
#define MAP_HPP

#include "binary_search_tree.hpp"
#include "reverse_iterator.hpp"
#include <utility>

/* ******************************************************************************
 * Thank god : https://www.cs.odu.edu/~zeil/cs361/latest/Public/maps/index.html *
 ********************************************************************************/

namespace ft {

    template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
    class map {
        public:

            typedef Key                             key_type;
            typedef T                               mapped_type;
            typedef ft::pair<key_type, mapped_type> value_type;
            typedef Compare                         key_compare;

            typedef Alloc                                       allocator_type;
            typedef typename allocator_type::pointer            pointer;
            typedef typename allocator_type::const_pointer      const_pointer;
            typedef typename allocator_type::reference          reference;
            typedef typename allocator_type::const_reference    const_reference;

            typedef typename ft::BinarySearchTree<value_type, key_type>::iterator       iterator;
            typedef typename ft::BinarySearchTree<value_type, key_type>::const_iterator const_iterator;
            typedef typename ft::reverse_iterator<iterator>                             reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator>                       const_reverse_iterator;
            typedef size_t                                                              size_type;
            typedef typename ft::iterator_traits<iterator>::difference_type             difference_type;

            // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
            class value_compare : public std::binary_function<value_type, value_type, bool>
            {
                friend class map<key_type, mapped_type, key_compare, allocator_type>;

            protected:
                Compare comp;
                value_compare(Compare c) : comp(c) {}  // constructed with map's comparison object

            public:
                /** Compares x.first and y.first by calling the stored key comparison function comp.
                 * @param x : pair x
                 * @param y : pair y
                 * @return : true if first components of lhs and rhs are equal; false, otherwise.
                 *
                 * Stored in binary_function :
                 * typedef bool result_type;
                 * typedef value_type first_argument_type;
                 * typedef value_type second_argument_type;
                 */
                bool operator() (const value_type &x, const value_type &y) const {
                    return comp(x.first, y.first);
                }
            };

        private:
            allocator_type                          _alloc;
            key_compare                             _comp;
            BinarySearchTree<value_type, key_type>  _bstree;
            size_type                               _size;

        public:

            /* *****************************************************************************
             *                           ALLOCATION/DEALLOCATION                           *
             *******************************************************************************/

            /** empty : Constructs an empty container, with no elements.
             *
             * @param comp = key_compare()
             * @param alloc = allocator_type()
             */
            explicit map (const key_compare& comp = key_compare(),
                          const allocator_type& alloc = allocator_type()) :
                          _alloc(alloc), _comp(comp), _bstree(), _size(0) {}

            /** range : Constructs a container with as many elements as the range [first,last],
             * with each element constructed from its corresponding element in that range.
             *
             * @param first : iterator first
             * @param last : iterator last
             */
            template <class InputIterator>
            map (InputIterator first, InputIterator last,
                 const key_compare& comp = key_compare(),
                 const allocator_type& alloc = allocator_type()) :
                 _alloc(alloc), _comp(comp), _bstree(), _size(0)
            {
                insert(first, last);
            }

            /** copy : Constructs a container with a copy of each of the elements in x
             * creates a container that keeps and uses copies of x's allocator and comparison object.
             *
             * @param x : another map to cpy
             */
            map (const map &x) : _alloc(x._alloc), _comp(x._comp), _bstree(), _size(0)
            {
                // TODO : use insert() as vector
                *this = x;
            }

            ~map()
            {
                //this->clear();
            }

            map &operator=(const map &x)
            {
                if (this == &x)
                    return (*this);
                //this->clear();

                //TODO : use insert() as vector
                this->_alloc = x._alloc;
                this->_comp = x._comp;
                this->_bstree = x._bstree;
                this->_size = x._size;
                return (*this);
            }

            /* *****************************************************************************
             *                                  ITERATORS                                  *
             *******************************************************************************/

            iterator begin() { return (_bstree.begin()); }
            const_iterator begin() const {return ( _bstree.begin()); }
            iterator end() { return (_bstree.end()); }
            const_iterator end() const { return (_bstree.end()); }

            reverse_iterator rbegin() { return (reverse_iterator(this->end())); }
            const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->end())); }
            reverse_iterator rend() { return (reverse_iterator(this->begin())); }
            const_reverse_iterator rend() const { return (const_reverse_iterator(this->begin())); }

            /* *****************************************************************************
             *                                  CAPACITY                                   *
             *******************************************************************************/

            bool empty() const { return (_bstree.isEmpty()); }
            size_type size() const { return (this->_size); }
            size_type max_size() const { return (_alloc.max_size()); }

            /* *****************************************************************************
             *                                ELEMENT ACCESS                               *
             *******************************************************************************/

            /*mapped_type &operator[](const key_type &k)
            {
                (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
            }*/

            /* Added in C++11 :
             * mapped_type &at(const key_type &k);
             * const mapped_type &at(const key_type &k) const;
             */

            /* *****************************************************************************
             *                                 MODIFIERS                                   *
             *******************************************************************************/
            void swap(map &x)
            {
                if (this != &x)
                {
                    allocator_type  tmp_alloc = x._alloc;
                    key_compare     tmp_comp = x._comp;
                    size_type       tmp_size = x._size;

                    this->_alloc = x._alloc;
                    this->_comp = x._comp;
                    this->_size = x._size;

                    x._alloc = tmp_alloc;
                    x._comp = tmp_comp;
                    x._size = tmp_size;

                    _bstree.swap(x);
                }
            }

            /** insert() : only one element to insert
             * Call the insert() method of BSTree
             *
             * @param x : element to insert
             * @return : ft::pair which contains an iterator on the new elements and true boolean if the element was added
             */
            ft::pair<iterator, bool> insert(const value_type &x)
            {
                bool is_added = false;

                iterator ret = _bstree.insert(x, is_added); // is_added will be true if an element was inserted
                if (is_added == true)
                    this->_size += 1;
                return (ft::make_pair(ret, is_added));
            }

            /** insert() : position is useless here because we are using a BST to store data
             *
             * @param position (void)
             * @param x : value_type to insert in our map
             * @return : iterator on the added element, or on an element which contains the same key
             */
            iterator insert(iterator position, const value_type &x)
            {
                (void)position;
                bool is_added = false;

                iterator ret = _bstree.insert(x, is_added);
                if (is_added == true)
                    this->_size += 1;
                return (ret);
            }

            template<class InputIterator>
            void insert(InputIterator first, InputIterator last)
            {
                bool is_added = false;

                while (first != last)
                {
                    _bstree.insert(*first++, is_added);
                    if (is_added == true)
                    {
                        this->_size += 1;
                        is_added = false;
                    }
                }
            }

            void erase(iterator position)
            {
                bool is_removed = true;

                _bstree.remove(*position, is_removed);
                if (is_removed == true)
                    this->_size -= 1;
            }

            size_type erase(const key_type &x)
            {
                bool is_removed = true;

                _bstree.remove(x, is_removed);
                if (is_removed == true) {
                    this->_size -= 1;
                    return (1);
                }
                return (0);
            }

            void erase(iterator first, iterator last)
            {
                bool is_removed = true;

                while (first != last)
                {
                    _bstree.remove(*first++, is_removed);
                    if (is_removed == true)
                        this->_size -= 1;
                    is_removed = false;
                }
            }

            void clear()
            {
                erase(this->begin(), this->end());
            }

            /* *****************************************************************************
             *                                 OBSERVERS                                   *
             *******************************************************************************/

            key_compare key_comp() const { return (key_compare()); }

            value_compare value_comp() const { return (value_compare(key_compare())); }

            /* *****************************************************************************
             *                                 OBSERVERS                                   *
             *******************************************************************************/

            iterator find(const key_type &x) { return (_bstree.find(x)); }
            const_iterator find(const key_type &x) const { return (_bstree.find(x)); }

            size_type count(const key_type &x) const { return (_bstree.containsKey(x)); }

            /** lower_bound() :  .**
             *
             * @param k : key to find
             * @return : iterator to the the first element in the container whose key is not considered to go before k
             * ( it is equivalent or goes after), or map::end if all keys are considered to go before k
             */
            iterator lower_bound(const key_type &k)
            {
                iterator it = begin();

                while (it != end())
                {
                    if (_comp((*it).first, k) == false) // *it.first < k == false : we use this semantic to include (*it)).first == k
                        return (it);
                    it++;
                }
                return (it);
            }

            const_iterator lower_bound(const key_type &k) const
            {
                const_iterator it = begin();

                while (it != end())
                {
                    if (_comp((*it).first, k) == false) // *it.first < k == false : we use this semantic to include (*it)).first == k
                        return (it);
                    it++;
                }
                return (it);
            }

            iterator upper_bound(const key_type &k)
            {
                iterator it = begin();

                while (it != end())
                {
                    if (_comp(k, (*it).first)) // k < *it.first : we use this semantic to exclude k == (*it)).first
                        return (it);
                    it++;
                }
                return (it);
            }

            const_iterator upper_bound(const key_type &k) const
            {
                const_iterator it = begin();

                while (it != end())
                {
                    if (_comp(k, (*it).first)) // k < *it.first : we use this semantic to exclude k == (*it)).first
                        return (it);
                    it++;
                }
                return (it);
            }

            ft::pair<iterator, iterator> equal_range(const key_type &k)
            {
                return (ft::make_pair(lower_bound(k), upper_bound(k)));
            }

            ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
            {
                return (ft::make_pair(lower_bound(k), upper_bound(k)));
            }

            /* *****************************************************************************
             *                                 CUSTOMS                                     *
             *******************************************************************************/
            void printMap() { _bstree.printTree(); }

    };
}


#endif // MAP_HPP
#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include "node.hpp"
#include "pair.hpp"
#include "iterator_traits.hpp"

/*-----------------------------------------------------------------------------------------------*
 * THANKS GOD :                                                                                  *
 * - Index : https://www.cs.odu.edu/~zeil/cs361/latest/Directory/outline/                        *
 * - Tree iterator : https://www.cs.odu.edu/~zeil/cs361/latest/Public/treetraversal/index.html-- *
 * - Tree : https://www.cs.odu.edu/~zeil/cs361/latest/Public/bst/index.html                      *
 *-----------------------------------------------------------------------------------------------*/

// TODO : find() function

namespace ft {

    /* Compare : binary predicate that takes two value keys as arguments and returns a bool.
     *      - comp(a,b) : comp is an object of this type and a and b are key values
     *      - shall return true if a is considered to go before b in the strict weak ordering the function defines.
     *      
     *  Template T : we gonna use this BST for Map, which uses pair to store data
     *      - value_type is a pair
     */

    //template < class T, class Compare, class Node = ft::Node<T>,
    //class Alloc = std::allocator<T>, class Node_Alloc = std::allocator<Node> >

    template < class T, class Key, class Compare = std::less<Key>, class Node = ft::Node<T>, class Alloc = std::allocator<T>, class Node_Alloc = std::allocator<Node> >
    class BinarySearchTree {

        public:
            typedef T           value_type;
            typedef Key         key_type;
            typedef Node        node;
            typedef Alloc       allocator_type;
            typedef Node_Alloc  node_alloc;
            typedef size_t      size_type;

        template <typename P>
        class BstIterator {

            public :
//                typedef P               value_type;
//                typedef P*              pointer;
//                typedef P&              reference;
                typedef P    value_type;
                typedef std::ptrdiff_t  difference_type;
                typedef P*   pointer;
                typedef P& reference;
                typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;

            private:
                friend class BinarySearchTree;

                // nodePtr is the current location in the tree. we can move
                // freely about the tree using left, right, and parent.
                // tree is the address of the BinarySearchTree object associated
                // with this iterator. it is used only to access the
                // root pointer, which is needed for ++ and --
                // when the iterator value is end()
                node *_nodePtr;
                const BinarySearchTree *_treePtr;

            public:

                BstIterator() : _nodePtr(NULL), _treePtr(NULL) {};
                BstIterator(node *n, const BinarySearchTree *t) : _nodePtr(n), _treePtr(t) {};
                BstIterator(const BstIterator &rhs) : _nodePtr(rhs._nodePtr), _treePtr(rhs._treePtr) {}
                ~BstIterator() {}

                BstIterator &operator=(const BstIterator &rhs)
                {
                    if (this == &rhs)
                        return (*this);
                    this->_nodePtr = rhs._nodePtr;
                    this->_treePtr = rhs._treePtr;
                    return (*this);
                }

                operator BstIterator<const P>() const
                {
                    return (BstIterator<const P>(this->_nodePtr, this->_treePtr));
                }

                /** dereference operator
                 *
                 * @return : return a reference to the value pointed to by nodePtr
                 */
                reference operator* () const { return (_nodePtr->value); }

                /** pointer operator
                 *
                 * @return : return a pointer to the value pointed to by nodePtr
                 */
                pointer operator->() const { return (&(_nodePtr->value)); }

                // comparison operators. just compare node pointers
                bool operator== (const BstIterator &rhs) const
                {
                    return (this->_nodePtr == rhs._nodePtr);
                }

                bool operator!= (const BstIterator &rhs) const
                {
                    return (this->_nodePtr != rhs._nodePtr);
                }

                // preincrement. move forward to next larger value
                BstIterator &operator++ ()
                {
                    node *p;

                    if (_nodePtr == NULL)
                    {
                        // ++ from end(). get the root of the tree
                        _nodePtr = _treePtr->_root;

                        // error! ++ requested for an empty tree
                        if (_nodePtr == NULL)
                            throw std::exception();

                        // move to the smallest value in the tree,
                        // which is the first node inorder
                        while (_nodePtr->left != NULL) {
                            _nodePtr = _nodePtr->left;
                        }
                    }
                    else
                    {
                        /* Left part of subtree is already visited
                         * Going to right part, then go down on left part of this new node
                         * Successor is the farthest left node of right subtree
                         */
                        if (_nodePtr->right != NULL) {
                            _nodePtr = _nodePtr->right;

                            while (_nodePtr->left != NULL) {
                                _nodePtr = _nodePtr->left;
                            }
                        }
                            /* Have already processed the left subtree, and there is no right subtree.
                             * Move up the tree, looking for a parent for which _nodePtr is a left child, stopping if the parent becomes NULL.
                             * A non-NULL parent is the successor. if parent is NULL, the original node was the last node inorder
                             * Its successor is the end of the list
                             */
                        else {
                            p = _nodePtr->parent;
                            while (p != NULL && _nodePtr == p->right) {
                                _nodePtr = p;
                                p = p->parent;
                            }
                            /* if we were previously at the right-most node in the tree
                             * -> _nodePtr = NULL
                             * The iterator specifies the end of the list
                             */
                            _nodePtr = p;
                        }
                    }
                    return (*this);
                }

                // postincrement
                BstIterator operator++ (int)
                {
                    BstIterator tmp = *this;
                    ++(*this);
                    return (tmp);
                }

                // predecrement. move backward to largest value < current value
                BstIterator  operator-- ()
                {
                    node *p;

                    if (_nodePtr == NULL)
                    {
                        _nodePtr = _treePtr->_root;

                        if (_nodePtr == NULL)
                            throw std::exception();

                        while (_nodePtr->right != NULL) {
                            _nodePtr = _nodePtr->right;
                        }
                    }
                    else
                    {
                        if (_nodePtr->left != NULL) {
                            _nodePtr = _nodePtr->left;

                            while (_nodePtr->right != NULL) {
                                _nodePtr = _nodePtr->right;
                            }
                        }
                        else {
                            p = _nodePtr->parent;
                            while (p != NULL && _nodePtr == p->left) {
                                _nodePtr = p;
                                p = p->parent;
                            }
                            _nodePtr = p;
                        }
                    }
                    return (*this);
                }

                // postdecrement
                BstIterator  operator-- (int)
                {
                    BstIterator tmp = *this;
                    --(*this);
                    return (tmp);
                }
        };

        private:
            node_alloc  _alloc;
            node        *_root;

            /** insert() : iterate in our tree using Compare to cross the tree and find the good place
             *
             * @param root : start with root, then iterator inside
             * @param parent : parent of the current root
             * @param to_insert : value_type to_insert in our tree
             * @param is_added : boolean who comes true if an element is inserted
             * @return
             */
            node *insert(node *&root, node *parent, const value_type &to_insert, bool &is_added)
            {
                if (root == NULL)
                {
                    root = _alloc.allocate(1);
                    _alloc.construct(root, node(to_insert, NULL, NULL, parent));
                    is_added = true;
                    return (root);
                }
                else if (Compare()(to_insert.first, root->value.first)) // to_insert.first < root->value.first : left
                    return (insert(root->left, root, to_insert, is_added));
                else if (Compare()(root->value.first, to_insert.first)) // to_insert.first > root->value.first : left
                    return (insert(root->right, root, to_insert, is_added));
                else
                    return (root);
            }

            /** remove () Internal method to remove from a subtree.
            *
            * @param x is the item to remove.
            * @param t is the node that roots the subtree.
            * Set the new root of the subtree.
            */
            void remove( const value_type &x, node *&n, bool &is_removed )
            {
                if ( n == NULL )
                {
                    is_removed = false;
                    return;   // Item not found; do nothing
                }
                if ( Compare()(x.first, n->value.first) )
                    remove( x, n->left, is_removed );
                else if ( Compare()(n->value.first, x.first) )
                    remove( x, n->right, is_removed );
                else if( n->left != NULL && n->right != NULL ) // Two children
                {
                    node *tmp = findMin(n->right);
                    n->value = tmp->value;

                    remove( n->value, n->right, is_removed );
                }
                else
                {
                    node *oldNode = n;

                    n = ( n->left != NULL ) ? n->left : n->right;
                    // re Set parent !
                    if (n)
                        n->parent = oldNode->parent;
                    _alloc.destroy(oldNode);
                    _alloc.deallocate(oldNode, 1);
                }
            }

            void remove( const key_type &x, node *&n, bool &is_removed )
            {
                if ( n == NULL )
                {
                    is_removed = false;
                    return;   // Item not found; do nothing
                }
                if ( Compare()(x, n->value.first) )
                    remove( x, n->left, is_removed );
                else if ( Compare()(n->value.first, x) )
                    remove( x, n->right, is_removed );
                else if ( n->left != NULL && n->right != NULL ) // Two children
                {
                    node *tmp = findMin(n->right);
                    n->value = tmp->value;

                    remove( n->value.first, n->right, is_removed );
                }
                else
                {
                    node *oldNode = n;

                    n = ( n->left != NULL ) ? n->left : n->right;
                    // re Set parent !
                    if (n)
                        n->parent = oldNode->parent;
                    _alloc.destroy(oldNode);
                    _alloc.deallocate(oldNode, 1);
                }
            }

            /** makeEmpty() : method to make subtree empty.
             *
             * @param t : starting with root
             */
            void makeEmpty( node *&root )
            {
                if (root != NULL)
                {
                    makeEmpty( root->left );
                    makeEmpty( root->right );
                    _alloc.destroy(root);
                    _alloc.deallocate(root, 1);
                }
                root = NULL;
            }

            void printBT(const std::string& prefix, const Node* node, bool isLeft)
            {
                if ( node != NULL )
                {
                    std::cout << prefix;

                    std::cout << (isLeft ? "├──" : "└──" );

                    // print the value of the node
                    std::cout << node->value.first << std::endl;

                    // enter the next tree level - left and right branch
                    printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
                    printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
                }
            }

        public:

            typedef BstIterator<value_type>                 iterator;
            typedef BstIterator<const value_type>           const_iterator;

            BinarySearchTree() : _root(NULL) {}

            /* Copy constructor */
            BinarySearchTree(const BinarySearchTree &rhs) : _root(NULL) {
                _root = clone( rhs._root );
            }

            /* Destructor */
            ~BinarySearchTree() {
                makeEmpty(_root);
            }

            /* Copy assignment */
            BinarySearchTree &operator=( const BinarySearchTree &rhs )
            {
                if (this == &rhs)
                    return (*this);
                this->_alloc = rhs._alloc;
                this->_root = rhs._root;
                return (*this);
            }

            node *getRoot () const { return this->_root; }

            /** isEmpty() : Test if the tree is logically empty.
             *
             * @return : true if empty, false otherwise.
             */
            bool isEmpty( ) const { return (_root == NULL); }

            void makeEmpty () { makeEmpty(this->_root); }

            /** insert() : Internal method to insert into a subtree.
            *
            * @param x : is the item to insert.
            * @param t : is the node that roots the subtree.
            * Set the new root of the subtree.
            */
            iterator insert(const value_type &to_insert, bool &is_added)
            {
                node* tmp = insert(_root, NULL, to_insert, is_added);
                return iterator(tmp, this); // iterator required two args
            }

            /** remove() : Public who calls the private methods
             *
             * @param to_remove : value_type to erase
             */
            void remove (const value_type &to_remove, bool &is_removed) { remove(to_remove, this->_root, is_removed); }
            void remove (const key_type &to_remove, bool &is_removed) { remove(to_remove, this->_root, is_removed); }

            /** findMin() : Internal method to find the smallest item in a subtree t.
             *
             * @param root : starting with root to iterator all the tree
             * @return : node containing the smallest item.
             */
            node *findMin(node *root) const
            {
                node *tmp = root;

                if (isEmpty())
                    return NULL;
                if (tmp->left == NULL)
                    return (tmp);
                while (tmp && tmp->left != NULL)
                    tmp = tmp->left;
                return (tmp);
            }

            /** findMax() : Internal method to find the largest item in a subtree t.
             *
             * @param root : starting with root to iterator all the tree
             * @return : node containing the largest item.
             */
            node *findMax(node *root) const
            {
                node *tmp = root;

                if (isEmpty())
                    return NULL;
                if (tmp != NULL)
                    while( tmp && tmp->right != NULL )
                        tmp = tmp->right;
                return (tmp);
            }

            /** contains() : Internal method to test if an item is in a subtree.
             *
             * @param x : is item to search for.
             * @param t : is the node that roots the subtree.
             * @return : true if find
             */
            bool contains( const value_type &x, node *t ) const
            {
                if (t == NULL)
                    return (false);
                else if( Compare()(x.first, t->value.first) )
                    return contains( x, t->left );
                else if( Compare()(t->value.first, x.first) )
                    return contains( x, t->right );
                else
                    return (true);    // Match
            }
            /***************NON RECURSIVE VERSION*****************
            bool     contains( const value_type & x, Node *t ) const
            {
                while( t != NULL )
                    if( x < t->value )
                        t = t->left;
                    else if( t->value < x )
                        t = t->right;
                    else
                        return true;    // Match

                return false;   // No match
                }
            *****************************************************/

            /** find() : Function who find a value_type
             *
             * @param to_find : value_type to find
             * @return : iterator of the value_type to_find
             */
            iterator find(const value_type &to_find)
            {
                node *tmp = this->_root;

                if (tmp == NULL)
                    return (end());
                while (tmp != NULL && tmp->value.first != to_find.first)
                    tmp = (Compare()(to_find.first, tmp->value.first) ? tmp->left : tmp->right);
                return (iterator(tmp, this)); // First constructor of iterator need node + tree
            }

            const_iterator find(const value_type &to_find) const
            {
                node *tmp = this->_root;

                if (tmp == NULL)
                    return (end());
                while (tmp != NULL && tmp->value.first != to_find.first)
                    tmp = (Compare()(to_find.first, tmp->value.first) ? tmp->left : tmp->right);
                return (const_iterator(tmp, this));
            }

            /** clone() : recursive function who clone all node in a tree
             *
             * @param root : starting root to iterate entire tree
             * @return : root node
             */
            node *clone( node *root )
            {
                if (root == NULL)
                    return NULL;
                else
                {
                    node *tmp = _alloc.allocate(1);
                    _alloc.construct(tmp, node(root->value, clone(root->left), clone(root->right), root->parent));
                    return (tmp);
                }
            }

            void printTree() { printBT("", this->_root, false); }

            /* ********************************************************************************
             *                      FUNCTIONS FOR OUR MAP IMPLEMENTATION                      *
             **********************************************************************************/
            iterator begin() { return (iterator(findMin(this->_root), this)); }
            const_iterator begin() const { return (const_iterator(findMin(this->_root), this)); }

            iterator end() { return (iterator(NULL, this)); }
            const_iterator end() const { return (const_iterator(NULL, this)); }

            void swap(BinarySearchTree &x)
            {
                if (this != &x) {
                    node_alloc tmp_alloc = this->_alloc;
                    node *tmp_root = this->_root;

                    this->_alloc = x._alloc;
                    this->_root = x._root;

                    x._alloc = tmp_alloc;
                    x._root = tmp_root;
                }
            }

            /** find() : Function who find a key_type
            *
            * @param to_find : key_type to find
            * @return : iterator of the key_type to_find
            */
            iterator find(const key_type &to_find)
            {
                node *tmp = this->_root;

                if (tmp == NULL)
                    return (end());
                while (tmp != NULL && tmp->value.first != to_find)
                    tmp = (Compare()(to_find, tmp->value.first) ? tmp->left : tmp->right);
                return (iterator(tmp, this));
            }

            const_iterator find(const key_type &to_find) const
            {
                node *tmp = this->_root;

                if (tmp == NULL)
                    return (end());
                while (tmp != NULL && tmp->value.first != to_find)
                    tmp = (Compare()(to_find, tmp->value.first) ? tmp->left : tmp->right);
                return (const_iterator(tmp, this));
            }

            /** containsKey() : same as contains() but use a key_type as item to find
             *
             * @param x : key_type to find
             * @return : 1 if found, 0 otherwise
             */
            size_type containsKey( const key_type &x ) const
            {
                node *t = this->_root;

                if (t == NULL)
                    return (0);
                while (t != NULL && x != t->value.first)
                {
                    if ( Compare()(x, t->value.first) )
                        t = t->left;
                    else if( Compare()(t->value.first, x.first) )
                        t = t->right;
                    else
                        return (1);
                }
                return (0);
            }
    };
}

#endif // BINARY_SEARCH_TREE_HPP
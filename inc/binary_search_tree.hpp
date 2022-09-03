#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include "node.hpp"
#include "pair.hpp"

/*-----------------------------------------------------------------------------------------*
 * THANKS GOD : https://www.cs.odu.edu/~zeil/cs361/latest/Public/treetraversal/index.html--*
 *-----------------------------------------------------------------------------------------*/

namespace ft {

    /* Compare : binary predicate that takes two value keys as arguments and returns a bool.
     *      - comp(a,b) : comp is an object of this type and a and b are key values
     *      - shall return true if a is considered to go before b in the strict weak ordering the function defines.
     *      
     *  Template T : we gonna use this BST for Map, which uses pair to store data
     *      - value_type is a pair
     */
    template < class T, class Compare = std::less<T>, class Node = ft::Node<T>,
                class Alloc = std::allocator<T>, class Node_Alloc = std::allocator<Node> >
    class BinarySearchTree {

        public:
            typedef T           value_type;
            typedef Node        node;
            typedef Alloc       allocator_type;
            typedef Node_Alloc  node_alloc;


        private:
            node_alloc  _alloc;
            node        *_root;

            /*
             * Recursive Function :
             *      - start = _root
             *      - we gonna iterate in our tree using Compare to cross the tree and find the good place
             *      - when its done, start is NULL and we can allocate and store content inside
             */
            node *insert(node *start, node *parent, const value_type &val)
            {
                if (start == NULL)
                {
                    start = _alloc.allocate(1);
                    _alloc.construct(start, node(val, parent));
                    return (start);
                }
                else if (Compare()(val.first, start->value.first)) // val.first < start->value.first : left
                    return (insert(start->left, start, val));
                else if (Compare()(start->value.first, val.first)) // val.first > start->value.first : left
                    return (insert(start->right, start, val));
                return (start);
            }
            
        public:
        
            template <typename P>
            class BstIterator : public ft::iterator<ft::bidirectional_iterator_tag, value_type> {
                
                typedef typename P::value_type                  value_type;

                public:
                    BstIterator() : _nodePtr(NULL), _treePtr(NULL) {};
                    BstIterator(const node *n, const BinarySearchTree *t) : _nodePtr(n), _treePtr(t) {};
                    BstIterator(const BstIterator &rhs) : _nodePtr(rhs._nodePtr), _treePtr(rhs._treePtr) {}
                    ~BstIterator() {}

                    BstIterator &operator=(const BstIterator &rhs)
                    {
                        if (this == &rhs)
                            return (*this);
                        this->_nodePtr = rhs._nodePtr;
                        this->_treePtr = rhs._treePtr;
                    }

                    // comparison operators. just compare node pointers
                    bool operator== (const BstIterator &rhs) const
                    {
                        return (this->_nodePtr == rhs._nodePtr);
                    }
        
                    bool operator!= (const BstIterator &rhs) const
                    {
                        return (this->_nodePtr != rhs._nodePtr);
                    }
        
                    // dereference operator. return a reference to
                    // the value pointed to by nodePtr
                    const value_type &operator* () const
                    {
                        return (this->_nodePtr->value);
                    }
        
                    // preincrement. move forward to next larger value
                    BstIterator& operator++ ()
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

                private:
                    friend class BinarySearchTree;

                    // nodePtr is the current location in the tree. we can move
                    // freely about the tree using left, right, and parent.
                    // tree is the address of the BinarySearchTree object associated
                    // with this iterator. it is used only to access the
                    // root pointer, which is needed for ++ and --
                    // when the iterator value is end()
                    const node *_nodePtr;
                    const BinarySearchTree *_treePtr;
            };

            typedef BstIterator<value_type>                 iterator;
            typedef BstIterator<const value_type>           const_iterator;

            BinarySearchTree( ) : _root(NULL) {}

            /* Copy constructor */
            BinarySearchTree( const BinarySearchTree & rhs ) : _root(NULL) {
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

            /** isEmpty() : Test if the tree is logically empty.
             *
             * @return : true if empty, false otherwise.
             */
            bool isEmpty( ) const
            {
                return (_root == NULL);
            }

            /** findMin() : Internal method to find the smallest item in a subtree t.
             *
             * @param t : subtree
             * @return : node containing the smallest item.
             */
            node *findMin(node *t) const
            {
                node *tmp = t;

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
             * @param t : subtree
             * @return : node containing the largest item.
             */
            node *findMax(node *t) const
            {
                node *tmp = t;

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
            bool containsKey( const value_type &x, node *t ) const
            {
                if (t == NULL)
                    return (false);
                else if( Compare()(x->value.first, t->value.first) )
                    return contains( x, t->left );
                else if( Compare()(t->value.first, x->value.first) )
                    return contains( x, t->right );
                else
                    return (true);    // Match
            }
            /******NON RECURSIVE VERSION*************************
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

            /** insert() : Internal method to insert into a subtree.
             *
             * @param x : is the item to insert.
             * @param t : is the node that roots the subtree.
             * Set the new root of the subtree.
             */
            iterator insert(const value_type &x) {
                node* tmp = insert(_root, NULL, x);
                reSetParent(_root);
                return iterator(tmp, this);
            }

            /** reSetParent() : Reorganize all parent pointer inside the tree, recursively
             *
             * @param current : start with _root
             */
            void reSetParent(node *current) {
                if (current)
                {
                    if (current->left != NULL) {
                        current->left->parent = current;
                        reSetParent(current->left);
                    }
                    if (current->right != NULL) {
                        current->right->parent = current;
                        reSetParent(current->right);
                    }
                }
            }

            /** remove () Internal method to remove from a subtree.
             *
             * @param x is the item to remove.
             * @param t is the node that roots the subtree.
             * Set the new root of the subtree.

             */
            void remove( const value_type &x, node *&n )
            {
                if ( n == NULL )
                    return;   // Item not found; do nothing
                if ( Compare(x.first, n->value.first) )
                    remove( x.first, n->left );
                else if ( Compare(n->value.first, x.first) )
                    remove( x.first, n->right );
                else if( n->left != NULL && n->right != NULL ) // Two children
                {
                    node *tmp = findMin(n->right);
                    n->value = tmp->value;

                    remove( n->value, n->right );
                }
                else
                {
                    node *oldNode = n;

                    n = ( n->left != NULL ) ? n->left : n->right;
                    // re Set parent !
                    if (n)
                        n->_parent = oldNode->_parent;
                    _alloc.destroy(oldNode);
                    _alloc.deallocate(oldNode, 1);
                }
            }

            /** makeEmpty() : method to make subtree empty.
             *
             * @param t : starting with root
             */
            void makeEmpty( node*& t )
            {
                if (t != NULL)
                {
                    makeEmpty( t->left );
                    makeEmpty( t->right );
                    _alloc.destroy(t);
                    _alloc.deallocate(t, 1);
                }
                t = NULL;
            }

            /** printTree() : print a subtree rooted at t in sorted order.
             *
             * @param t : starting with _root
             * @param out : outstream
             */
            /* printTree : Internal method to */
            void printTree( node *t, std::ostream &out ) const
            {
                if( t != NULL )
                {
                    printTree( t->left, out );
                    out << t->value << std::endl;
                    printTree( t->right, out );
                }
            }
    };
}

#endif // BINARY_SEARCH_TREE_HPP
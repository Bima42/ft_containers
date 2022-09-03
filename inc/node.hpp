#ifndef NODE_HPP
#define NODE_HPP

/* Template T : for map, it's gonna be a pair
 * So we can access : value.first ---- value.second
 */
namespace ft {

    template<typename T>
    struct Node {

        typedef T value_type;
        value_type value;
        Node<value_type> *parent;
        Node<value_type> *left;
        Node<value_type> *right;

        Node(const value_type &insert_value, Node *lft, Node *rgt, Node *prt) :
                value(insert_value),
                parent(prt),
                left(lft),
                right(rgt) {}

    };
}

#endif // NODE_HPP
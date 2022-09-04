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
        Node *left;
        Node *right;
        Node *parent;

        Node(const value_type &insert_value, Node *lft, Node *rgt, Node *prt) :
                value(insert_value),
                left(lft),
                right(rgt),
                parent(prt) {}

    };
}

#endif // NODE_HPP
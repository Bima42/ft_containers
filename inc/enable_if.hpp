#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

namespace ft {
    template<bool Cond, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> { typedef T type; };
}

/*
 * Family of templates
 * Is a set of tools to allow a function template or a class template specialization to include or exclude itself
 * from a set of matching functions or specializations based on properties of its template arguments.
 *
 * Type T is enabled as member type enable_if::type is Cond is true.
 * Otherwise, enable_if::type is not defined
 * When a particular condition is not met -> enable_if::type is not defined -> Compilation should fail
 */

#endif // ENABLE_IF_HPP

#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

/* TEST TO DO !!! CONST, VOLATILE ARE ACCEPTED BY IS_INTEGRAL ????? */

namespace ft {

    /*
     * Default struct is_integral :
     * template <class T>
     * struct is_integral : public integral_constant<bool, __is_integral(T)> {};
     * Inherit from integral_constant, contains boolean if the type is inside the list.
     */
    template <bool is_integral, typename T>
    struct integral_constant {
        typedef T type;
        static const bool value = is_integral;
    };

    /*
     * This is the default template.
     * If the type is from the list, boolean will be true
     * Otherwise false
     */
    template <typename>
    struct is_integral_value : public integral_constant<false, bool> {};

    /*
     * ------------------------- TRUE TYPE ----------------------------
     */

    template<>
    struct is_integral_value<bool> : public integral_constant<true, bool> {};

    template<>
    struct is_integral_value<char> : public integral_constant<true, char> {};

    template<>
    struct is_integral_value<wchar_t> : public integral_constant<true, wchar_t> {};

    template<>
    struct is_integral_value<signed char> : public integral_constant<true, signed char> {};

    template<>
    struct is_integral_value<int> : public integral_constant<true, int> {};

    template<>
    struct is_integral_value<short int> : public integral_constant<true, short int > {};

    template<>
    struct is_integral_value<long int> : public integral_constant<true, long> {};

    template<>
    struct is_integral_value<unsigned char> : public integral_constant<true, unsigned char> {};

    template<>
    struct is_integral_value<unsigned short int> : public integral_constant<true, unsigned short int> {};

    template<>
    struct is_integral_value<unsigned int> : public integral_constant<true, unsigned int> {};

    template<>
    struct is_integral_value<unsigned long int> : public integral_constant<true, unsigned long int> {};


    /*
     * ------------------------- NOT SUPPORTED C++98 ----------------------------
     */
    /*  template<>
     *  struct is_integral_value<long long int> : public integral_constant<true, long long int> {};
     *
     *  template<>
     *  struct is_integral_value<char16_t> : public integral_constant<true, char16_t> {};
     *
     *  template<>
     *  struct is_integral_value<char32_t> : public integral_constant<true, char32_t> {};
     *
     *  template<>
     *  struct is_integral_value<unsigned long long int> : public integral_constant<true, unsigned long long int> {};
     *  ------------------------------------------------------------------------------------------------------
     */

    /*
     * is_integral -> take the template given to test if it's an integral using is_integral_value
     *
     * ft::is_integral<test>::value will return the boolean, to know if test is an integral type.
     */
    template <class T>
    struct is_integral : public is_integral_value<T> {};

    /*
     * Volatile, Const and Volatile const are allowed for integral types
     */
    template <class T>
    struct is_integral<const T> : public is_integral_value<T> {};

    template <class T>
    struct is_integral<volatile T> : public is_integral_value<T> {};

    template <class T>
    struct is_integral<volatile const T> : public is_integral_value<T> {};
}

/*
 * FUNDAMENTAL INTEGRAL TYPES :
 * - bool
 * - char
 * - char16_t
 * - char32_t
 * - wchar_t
 * - signed char
 * - short int
 * - int
 * - long int
 * - long long int
 * - unsigned char
 * - unsigned short int
 * - unsigned int
 * - unsigned long int
 * - unsigned long long int
 */

#endif // IS_INTEGRAL_HPP
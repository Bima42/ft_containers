#include "inc/vector.hpp"
#include "inc/map.hpp"
#include <vector>
#include <list>
#include <map>
#include <memory>


/*template <typename Ite_1, typename Ite_2>
void ft_eq_ope(const Ite_1 &first, const Ite_2 &second, const bool redo = 1)
{
    std::cout << (first < second) << std::endl;
    std::cout << (first <= second) << std::endl;
    std::cout << (first > second) << std::endl;
    std::cout << (first >= second) << std::endl;
    if (redo)
        ft_eq_ope(second, first, 0);
}*/

template <typename T>
class foo {
public:
    typedef T	value_type;

    foo(void) : value(), _verbose(false) { };
    foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
    foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
    ~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
    void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
    void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
    foo &operator=(value_type src) { this->value = src; return *this; };
    foo &operator=(foo const &src) {
        if (this->_verbose || src._verbose)
            std::cout << "foo::operator=(foo) CALLED" << std::endl;
        this->value = src.value;
        return *this;
    };
    value_type	getValue(void) const { return this->value; };
    void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

    operator value_type(void) const {
        return value_type(this->value);
    }
private:
    value_type	value;
    bool		_verbose;
};

#define T1 int
#define T2 foo<int>
typedef ft::map<T1, T2>::value_type T3;
typedef ft::map<T1, T2>::iterator ft_iterator;
typedef ft::map<T1, T2>::const_iterator ft_const_iterator;

static int iter = 0;

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
    o << "key: " << iterator->first << " | value: " << iterator->second;
    if (nl)
        o << std::endl;
    return ("");
}

template <typename MAP>
void	ft_bound(MAP &mp, const T1 &param)
{
    ft_iterator ite = mp.end(), it[2];
    ft::pair<ft_iterator, ft_iterator> ft_range;

    std::cout << "\t-- [" << iter++ << "] --" << std::endl;
    std::cout << "with key [" << param << "]:" << std::endl;
    it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
    ft_range = mp.equal_range(param);
    std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
    std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
    std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
}

template <typename MAP>
void	ft_const_bound(const MAP &mp, const T1 &param)
{
    ft_const_iterator ite = mp.end(), it[2];
    ft::pair<ft_const_iterator, ft_const_iterator> ft_range;

    std::cout << "\t-- [" << iter++ << "] (const) --" << std::endl;
    std::cout << "with key [" << param << "]:" << std::endl;
    it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
    ft_range = mp.equal_range(param);
    std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
    std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
    std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
}


int main () {
    std::list<T3> lst;
    unsigned int lst_size = 10;
    for (unsigned int i = 0; i < lst_size; ++i)
        lst.push_back(T3(i + 1, (i + 1) * 3));
    ft::map<T1, T2> mp(lst.begin(), lst.end());

    ft_const_bound(mp, -10);
    ft_const_bound(mp, 1);
    ft_const_bound(mp, 5);
    ft_const_bound(mp, 10);
    ft_const_bound(mp, 50);


    mp.lower_bound(3)->second = 404;
    mp.upper_bound(7)->second = 842;
    ft_bound(mp, 5);
    ft_bound(mp, 7);

    /*{
        ft::map<int, int>::iterator it;
        it->first = 1;

        ft::map<int, int> test;
        int i = 12;
        int u = 25;
        ft::pair<int, int> test_pair = ft::make_pair(i, u);
        i = u + i;
        u += 199;
        ft::pair<int, int> test_pair2 = ft::make_pair(i, u);
        i = u + i;
        u += 199;
        ft::pair<int, int> test_pair3 = ft::make_pair(i, u);
        i = 5;
        u = 2;
        ft::pair<int, int> test_pair4 = ft::make_pair(i, u);
        i = 199;
        u = 2000;
        ft::pair<int, int> test_pair5 = ft::make_pair(i, u);
        i = 3;
        u = 2;
        ft::pair<int, int> test_pair6 = ft::make_pair(i, u);
        i = 8;
        u = 20;
        ft::pair<int, int> test_pair7 = ft::make_pair(i, u);
        i = 38;
        u = 20;
        ft::pair<int, int> test_pair8 = ft::make_pair(i, u);

        std::cout << "=======================FT_MAP================================" << std::endl;
        std::cout << "Is test tree empty ? " << test.empty() << std::endl;
        std::cout << "test pair 1: " << test_pair.first << " " << test_pair.second << std::endl;
        std::cout << "test pair 2: " << test_pair2.first << " " << test_pair2.second << std::endl;
        std::cout << "test pair 3: " << test_pair3.first << " " << test_pair3.second << std::endl;
        std::cout << "test pair 4: " << test_pair4.first << " " << test_pair4.second << std::endl;
        std::cout << "test pair 5: " << test_pair5.first << " " << test_pair5.second << std::endl;
        std::cout << "test pair 6: " << test_pair6.first << " " << test_pair6.second << std::endl;
        std::cout << "test pair 7: " << test_pair7.first << " " << test_pair7.second << std::endl;
        std::cout << "test pair 8: " << test_pair8.first << " " << test_pair8.second << std::endl;
        test.insert(test_pair);
        test.insert(test_pair2);
        test.insert(test_pair3);
        test.insert(test_pair4);
        test.insert(test_pair5);
        test.insert(test_pair6);
        test.insert(test_pair7);
        test.insert(test_pair8);

        std::cout << "Is test tree empty ? " << test.empty() << std::endl;
        test.printMap();
        std::cout << "Lower bound of 38 is :" << test.lower_bound(38)->first << std::endl;
        std::cout << "Upper bound of 38 is :" << test.upper_bound(38)->first << std::endl;

        std::cout << "Equal range 199 : " << test.equal_range(199).first->first << "  ||  " << test.equal_range(199).first->second << std::endl;
        std::cout << "Equal range 199 : " << test.equal_range(199).second->first << "  ||  " << test.equal_range(199).second->second << std::endl;
        //test.remove(test_pair);
        //test.remove(test_pair3);

        std::cout << "Find Pair 1 | 2 : " << test.find(test_pair4)->value.first << " | "
                  << test.find(test_pair4)->value.second << " His parent is : " <<
                  test.find(test_pair4)->parent->value.first <<
                  " | " << test.find(test_pair4)->parent->value.second << std::endl;
        test.printBT();
        test.makeEmpty();
        std::cout << "Is test tree empty ? " << test.isEmpty() << std::endl;
        test.printBT();

    }
    {

        std::map<int, int> test;
        int i = 12;
        int u = 25;
        std::pair<int, int> test_pair = std::make_pair(i, u);
        i = u + i;
        u += 199;
        std::pair<int, int> test_pair2 = std::make_pair(i, u);
        i = u + i;
        u += 199;
        std::pair<int, int> test_pair3 = std::make_pair(i, u);
        i = 1;
        u = 2;
        std::pair<int, int> test_pair4 = std::make_pair(i, u);
        i = 199;
        u = 2000;
        std::pair<int, int> test_pair5 = std::make_pair(i, u);
        i = 3;
        u = 2;
        std::pair<int, int> test_pair6 = std::make_pair(i, u);
        i = 8;
        u = 20;
        std::pair<int, int> test_pair7 = std::make_pair(i, u);
        i = 38;
        u = 20;
        std::pair<int, int> test_pair8 = std::make_pair(i, u);

        std::cout << "=======================STD_MAP================================" << std::endl;
        std::cout << "test pair 1: " << test_pair.first << " " << test_pair.second << std::endl;
        std::cout << "test pair 2: " << test_pair2.first << " " << test_pair2.second << std::endl;
        std::cout << "test pair 3: " << test_pair3.first << " " << test_pair3.second << std::endl;
        std::cout << "test pair 4: " << test_pair4.first << " " << test_pair4.second << std::endl;
        std::cout << "test pair 5: " << test_pair5.first << " " << test_pair5.second << std::endl;
        test.insert(test_pair);
        test.insert(test_pair2);
        test.insert(test_pair3);
        test.insert(test_pair4);
        test.insert(test_pair5);
        test.insert(test_pair6);
        test.insert(test_pair7);
        test.insert(test_pair8);
        std::cout << "Lower bound of 38 is :" << test.lower_bound(38)->first << std::endl;
        std::cout << "Upper bound of 38 is :" << test.upper_bound(38)->first << std::endl;

        std::cout << "Equal range 199 : " << test.equal_range(199).first->first << "  ||  " << test.equal_range(199).first->second << std::endl;
        std::cout << "Equal range 199 : " << test.equal_range(199).second->first << "  ||  " << test.equal_range(199).second->second << std::endl;

    }*/

    /*
    ft::map<int, int> test;
    int i = 10;
    int u = 20;
    ft::pair<int, int> pair1 = ft::make_pair(i, u);
    ft::map<int, int>::iterator it = test.begin();

    test.insert(it, pair1);
    it = test.begin();
    test.printTree();
    std::cout << "size = " << test.size() << std::endl;
    test.erase(it);

    ft::BinarySearchTree< ft::pair<int, int>, int > test;
    int i = 12;
    int u = 25;

    ft::pair<int, int> test_pair = ft::make_pair(i, u);
    std::cout << "Empty ? " << test.isEmpty() << std::endl;
    std::cout << test_pair.first << " " << test_pair.second << std::endl;
    test.insert(test_pair);
    std::cout << "Empty ? " << test.isEmpty() << std::endl;
    std::cout << "Contains test_pair ? " << test.containsKey(test_pair, test.getRoot()) << std::endl;

    ft::pair<int, int> test2 = ft::make_pair(u, i);
    i += 40;
    u += 10;
    ft::pair<int, int> test3 = ft::make_pair(u, i);

    i -= 60;
    u -= 80;
    ft::pair<int, int> test4 = ft::make_pair(u, i);

    test.insert(test2);
    test.insert(test3);
    test.insert(test4);

    std::cout << "Contains test2 ? " << test.containsKey(test2, test.getRoot()) << std::endl;
    std::cout << "Contains test3 ? " << test.containsKey(test3, test.getRoot()) << std::endl;
    std::cout << "Contains test4 ? " << test.containsKey(test4, test.getRoot()) << std::endl;

    test.remove(test2);

    std::cout << "Contains test2 ? " << test.containsKey(test2, test.getRoot()) << std::endl;
    std::cout << "Min : " << test.findMin(test.getRoot())->value.first << std::endl;
    std::cout << "Max : " << test.findMax(test.getRoot())->value.first << std::endl;

    test.printTree();
    ft::BinarySearchTree< ft::pair<int, int>, int > copy(test);
    copy.printTree();

    ft::BinarySearchTree< ft::pair<int, int>, int >::iterator it;
    it = test.begin();

    std::cout << "it = " << (*it).first << std::endl;
    ++it;
    std::cout << "++it = " << (*it).first << std::endl;
    ++it;
    std::cout << "++it = " << (*it).first << std::endl;


    //int i = 0;

    //ft::vector<int> ft2(10, 100);
    //std::vector<int> test_std1(10, 20);
    //std::vector<int> test_std2(3, 50);


    std::vector<int> v_int1, v_int2, v_int3;
    std::vector<std::string> v_str1, v_str2;
    ft::vector<int> V_int1, V_int2, V_int3;
    ft::vector<std::string> V_str1, V_str2;
    bool ret = false;

    v_int1.push_back(1);
    v_int3.push_back(1);
    v_str1.push_back("aa");
    v_str2.push_back("ab");
    std::cout << "-----------STD-------------" << std::endl;
    ret = v_int1 < v_int2;
    std::cout << "int1 < int2 : " << ret << std::endl;
    v_int2.push_back(2);
    ret = v_int1 < v_int2;
    std::cout << "int1 < int2 : " << ret << std::endl;
    ret = v_int1 < v_int3;
    std::cout << "int1 < int3 : " << ret << std::endl;
    ret = v_str1 < v_str2;
    std::cout << "str1 < str2 : " << ret << std::endl;

    std::cout << "-----------FT-------------" << std::endl;

    V_int1.push_back(1);
    V_int3.push_back(1);
    V_str1.push_back("aa");
    V_str2.push_back("ab");
    ret = V_int1 < V_int2;
    std::cout << "int1 < int2 : " << ret << std::endl;
    V_int2.push_back(2);
    ret = V_int1 < V_int2;
    std::cout << "int1 < int2 : " << ret << std::endl;
    ret = V_int3 < V_int3;
    std::cout << "int1 < int3 : " << ret << std::endl;
    ret = V_str1 < V_str2;
    std::cout << "str1 < str2 : " << ret << std::endl;


    const int size = 5;
    ft::vector<int> vct(size);
    ft::vector<int>::reverse_iterator it_0(vct.rbegin());
    ft::vector<int>::reverse_iterator it_1(vct.rend());
    ft::vector<int>::reverse_iterator it_mid;
    ft::vector<int>::const_reverse_iterator cit_0 = vct.rbegin();
    ft::vector<int>::const_reverse_iterator cit_1;
    ft::vector<int>::const_reverse_iterator cit_mid;
    for (int i = size; it_0 != it_1; --i) {
        std::cout << "*it = " << *it_0 << std::endl;
        *it_0++ = i;
    }
    it_0 = vct.rbegin();
    cit_1 = vct.rend();
    it_mid = it_0 + 3;
    cit_mid = it_0 + 3; cit_mid = cit_0 + 3; cit_mid = it_mid;
    std::cout << std::boolalpha;
    std::cout << ((it_0 + 3 == cit_0 + 3) && (cit_0 + 3 == it_mid)) << std::endl;
    std::cout << "\t\tft_eq_ope:" << std::endl;
    // regular it
    ft_eq_ope(it_0 + 3, it_mid);
    ft_eq_ope(it_0, it_1);
    ft_eq_ope(it_1 - 3, it_mid);
    // const it
    ft_eq_ope(cit_0 + 3, cit_mid);
    ft_eq_ope(cit_0, cit_1);
    ft_eq_ope(cit_1 - 3, cit_mid);
    // both it
    ft_eq_ope(it_0 + 3, cit_mid);
    ft_eq_ope(it_mid, cit_0 + 3);
    ft_eq_ope(it_0, cit_1);
    ft_eq_ope(it_1, cit_0);
    ft_eq_ope(it_1 - 3, cit_mid);
    ft_eq_ope(it_mid, cit_1 - 3);


         const int size = 5;
         ft::vector<int> vct(size);
         ft::vector<int>::reverse_iterator it(vct.rbegin());
         ft::vector<int>::const_reverse_iterator ite(vct.rend());
     
         for (int i = 1; it != ite; ++i)
             *it++ = (i * 7);
     
         it = vct.rbegin();
         ite = vct.rbegin();
     
         std::cout << *(++ite) << std::endl;
         std::cout << *(ite++) << std::endl;
         std::cout << *ite++ << std::endl;
         std::cout << *++ite << std::endl;
     
         it->m();
         ite->m();
     
         std::cout << *(++it) << std::endl;
         std::cout << *(it++) << std::endl;
         std::cout << *it++ << std::endl;
         std::cout << *++it << std::endl;
     
         std::cout << *(--ite) << std::endl;
         std::cout << *(ite--) << std::endl;
         std::cout << *--ite << std::endl;
         std::cout << *ite-- << std::endl;
     
         (*it).m();
         (*ite).m();
     
         std::cout << *(--it) << std::endl;
         std::cout << *(it--) << std::endl;
         std::cout << *it-- << std::endl;
         std::cout << *--it << std::endl;
         
         const int size = 5;
         ft::vector<int> vct(size);
         ft::vector<int>::reverse_iterator it(vct.rbegin());
         ft::vector<int>::const_reverse_iterator ite(vct.rend());
     
         for (int i = 1; it != ite; ++i)
             *it++ = (i * 7);
     
         it = vct.rbegin();
         ite = vct.rbegin();
     
         std::cout << *(++ite) << std::endl;
         std::cout << *(ite++) << std::endl;
         std::cout << *ite++ << std::endl;
         std::cout << *++ite << std::endl;
     
         it->m();
         ite->m();
     
         std::cout << *(++it) << std::endl;
         std::cout << *(it++) << std::endl;
         std::cout << *it++ << std::endl;
         std::cout << *++it << std::endl;
     
         std::cout << *(--ite) << std::endl;
         std::cout << *(ite--) << std::endl;
         std::cout << *--ite << std::endl;
         std::cout << *ite-- << std::endl;
     
         (*it).m();
         (*ite).m();
     
         std::cout << *(--it) << std::endl;
         std::cout << *(it--) << std::endl;
         std::cout << *it-- << std::endl;
         std::cout << *--it << std::endl;
         
         -------------------------Reverse_iterator---------------------------------
         const int size = 5;
         ft::vector<int> vct(size);
         ft::vector<int>::reverse_iterator it = vct.rbegin();
         ft::vector<int>::const_reverse_iterator ite = vct.rbegin();
     
         for (int i = 0; i < size; ++i)
             it[i] = (size - i) * 5;
     
         it = it + 5;
         std::cout << "it = it + 5 : " << *it << std::endl;
         it = 1 + it;
         std::cout << "it = 1 + it : " << *it << std::endl;
         it = it - 4;
         std::cout << "it = it - 4 : " << *it << std::endl;
     
         std::cout << "*(it += 2) : " << *(it += 2) << std::endl;
         std::cout << "*(it -= 1) : " << *(it -= 1) << std::endl;
         std::cout << "==================================" << std::endl;
     
         *(it -= 2) = 42;
         *(it += 2) = 21;
     
         std::cout << "ite : " << *ite << std::endl;
         std::cout << "it : " << *it << std::endl;
         std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;
     
         std::cout << "(it == const_it): " << (ite == it) << std::endl;
         std::cout << "(const_ite - it): " << (ite - it) << std::endl;
         std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;
         --------------------------Reverse_iterator---------------------------------
         const int size = 5;
         ft::vector<int> vct(size);
         ft::vector<int>::iterator it_ = vct.begin();
         ft::vector<int>::reverse_iterator it(it_);
         for (int i = 0; i < size; ++i)
             vct[i] = (i + 1) * 5;
     
         std::cout << (it_ == it.base()) << std::endl;
         std::cout << (it_ == (it + 3).base()) << std::endl;
     
         std::cout << *(it.base() + 1) << std::endl;
         std::cout << *(it - 3) << std::endl;
         std::cout << *(it - 3).base() << std::endl;
         it -= 3;
         std::cout << *it.base() << std::endl;
     
         std::cout << "TEST OFFSET" << std::endl;
         std::cout << *(it) << std::endl;
         std::cout << *(it).base() << std::endl;
         std::cout << *(it - 0) << std::endl;
         std::cout << *(it - 0).base() << std::endl;
         std::cout << *(it - 1).base() << std::endl;
     
     
         --------------------------------Const_reverse_iterator-----------------------------------
         ft::vector<std::string> ft1(10);
         ft::vector<std::string>::iterator it = ft1.begin();
         for (unsigned long int i = 0; i < ft1.size(); ++i)
             it[i] = std::string((ft1.size() - i), i + 65);
         ft1.push_back("coucou");
     
         it = ft1.begin();
         ft::vector<std::string>::const_reverse_iterator rit(it);
         ft::vector<std::string>::const_reverse_iterator rit2 = rit;
         ft::vector<std::string>::const_reverse_iterator rit3 = ft1.rend();
         ft::vector<std::string>::const_reverse_iterator rit4 = ft1.rbegin();
     
         std::cout << "it : " << *it << std::endl;
         std::cout << "Rit(it) : " << *rit << std::endl;
         std::cout << "Rit2 = rit : " << *rit2 << std::endl;
         std::cout << "Rit3 = end() : " << *rit3 << std::endl;
         std::cout << "Rit4 = begin() : " << *rit4 << std::endl;
     
     
         std::cout << "---------------------------Insert()---------------------------" << std::endl;
         std::cout << "------------------------STD_CONTAINER------------------------" << std::endl;
         std::vector<int>::iterator ret;
         std::vector<int>::iterator std_beg = test_std1.begin();
         std::vector<int>::iterator test1 = test_std2.begin();
         std::vector<int>::iterator test2 = test_std2.end();
         std_beg++;
     
         test_std1.insert(std_beg, test1, test2);
     
         for (std::vector<int>::iterator b = test_std1.begin(); b != test_std1.end(); b++)
             std::cout << *b << std::endl;
     
         std::cout << "------------------------FT_CONTAINER------------------------" << std::endl;
         ft::vector<int>::iterator ret2;
         ft::vector<int>::iterator ft_beg = ft1.begin();
         ft::vector<int>::iterator test3 = ft2.begin();
         ft::vector<int>::iterator test4 = ft2.end();
         ft_beg++;
     
         ft1.insert(ft_beg, test3, test4);
     
         for (ft::vector<int>::iterator b = ft1.begin(); b != ft1.end(); b++)
             std::cout << *b << std::endl;
     
         std::cout << "---------------------------Shrink_to_fit()---------------------------" << std::endl;
         std::cout << "------------------------FT_CONTAINER------------------------" << std::endl;
         ft1.pop_back();
         ft1.pop_back();
         std::cout << "Size : " << ft1.size() << std::endl;
         std::cout << "Capacity : " << ft1.capacity() << std::endl;
         std::cout << "##### Shrink to fit ........ ######" << std::endl;
         ft1.shrink_to_fit();
         std::cout << "Size : " << ft1.size() << std::endl;
         std::cout << "Capacity : " << ft1.capacity() << std::endl;
     
         std::cout << "------------------------STD_CONTAINER------------------------" << std::endl;
         test_std1.pop_back();
         test_std1.pop_back();
         std::cout << "Size : " << test_std1.size() << std::endl;
         std::cout << "Capacity : " << test_std1.capacity() << std::endl;
         std::cout << "##### Shrink to fit ........ ######" << std::endl;
         test_std1.shrink_to_fit();
         std::cout << "Size : " << test_std1.size() << std::endl;
         std::cout << "Capacity : " << test_std1.capacity() << std::endl;
     
         std::cout << "---------------------------Swap()---------------------------" << std::endl;
         std::cout << "------------------------FT_CONTAINER------------------------" << std::endl;
         std::cout << "Size 1 : " << ft1.size() << std::endl;
         std::cout << "Size 2 : " << ft2.size() << std::endl;
     
         std::cout << "Capacity 1 : " << ft1.capacity() << std::endl;
         std::cout << "Capacity 2 : " << ft2.capacity() << std::endl;
     
         std::cout << "Begin 1 : " << *(ft1.begin()) << std::endl;
         std::cout << "Begin 2 : " << *(ft2.begin()) << std::endl;
     
         std::cout << "##### Swap ........ ######" << std::endl;
         ft1.swap(ft2);
     
         std::cout << "Size 1 : " << ft1.size() << std::endl;
         std::cout << "Size 2 : " << ft2.size() << std::endl;
     
         std::cout << "Capacity 1 : " << ft1.capacity() << std::endl;
         std::cout << "Capacity 2 : " << ft2.capacity() << std::endl;
     
         std::cout << "Begin 1 : " << *(ft1.begin()) << std::endl;
         std::cout << "Begin 2 : " << *(ft2.begin()) << std::endl;
     
     
         std::cout << "------------------------STD_CONTAINER------------------------" << std::endl;
         std::cout << "Size 1 : " << test_std1.size() << std::endl;
         std::cout << "Size 2 : " << test_std2.size() << std::endl;
     
         std::cout << "Capacity 1 : " << test_std1.capacity() << std::endl;
         std::cout << "Capacity 2 : " << test_std2.capacity() << std::endl;
     
         std::cout << "Begin 1 : " << *(test_std1.begin()) << std::endl;
         std::cout << "Begin 2 : " << *(test_std2.begin()) << std::endl;
     
         std::cout << "##### Swap ........ ######" << std::endl;
         test_std1.swap(test_std2);
     
         std::cout << "Size 1 : " << test_std1.size() << std::endl;
         std::cout << "Size 2 : " << test_std2.size() << std::endl;
     
         std::cout << "Capacity 1 : " << test_std1.capacity() << std::endl;
         std::cout << "Capacity 2 : " << test_std2.capacity() << std::endl;
     
         std::cout << "Begin 1 : " << *(test_std1.begin()) << std::endl;
         std::cout << "Begin 2 : " << *(test_std2.begin()) << std::endl;
     
     
         std::cout << "--------------------push_back()---------------------------" << std::endl;
         std::cout << "ft_container           ||||||||           std_container       " << std::endl;
     
         ft::vector<int>::iterator ft_it = test_ft.begin();
         std::vector<int>::iterator std_it = test_std.begin();
         for (ft::vector<int>::iterator last = test_ft.end(); ft_it != last; ft_it++ ) {
             std::cout << *ft_it << "               |||||||" << "               " << *std_it++ << "      " << std::endl;
         }
     
         std::cout << "------------------PUSH_BACK : 50----------------------" << std::endl;
     
     
         std::cout << test_ft.size() << " ||||| " << test_ft.capacity() << std::endl;
         std::cout << test_std.size() << " ||||| " << test_std.capacity() << std::endl;
     
         test_ft.push_back(50);
         test_std.push_back(50);
     
         ft_it = test_ft.begin();
         std_it = test_std.begin();
     
         std::cout << test_ft.size() << " ||||| " << test_ft.capacity() << std::endl;
         std::cout << test_std.size() << " ||||| " << test_std.capacity() << std::endl;
     
         for (ft::vector<int>::iterator last = test_ft.end(); ft_it != last; ft_it++ ) {
             std::cout << *ft_it << "               |||||||" << "               " << *std_it++ << "      " << std::endl;
         }
     
         std::cout << std::endl << "--------------------resize()---------------------------" << std::endl;
     
         std::cout << "Ft : Resize > _size : " << std::endl;
         test_ft.resize(12);
         ft::vector<int>::iterator it1 = test_ft.begin();
         ft::vector<int>::iterator it2 = test_ft.end();
         for (; it1 != it2; it1++) {
             std::cout << *it1 << std::endl;
         }
     
         std::cout << "STD : Resize > _size : " << std::endl;
         test_std.resize(12);
         std::vector<int>::iterator it1s = test_std.begin();
         std::vector<int>::iterator it2s = test_std.end();
         for (; it1s != it2s; it1s++) {
             std::cout << *it1s << std::endl;
         }
     
         std::cout << std::endl << "--------------------assign()---------------------------" << std::endl;
     
         test_std.assign(2, 23);
         std::cout << "std vector size : " << test_std.size() << std::endl;
         std::cout << "std vector capacity : " << test_std.capacity() << std::endl;
         std::cout << "std vector @ [10] : " << test_std[10] << std::endl;
         test_ft.assign(2, 23);
         std::cout << "ft vector size : " << test_ft.size() << std::endl;
         std::cout << "ft vector capacity : " << test_ft.capacity() << std::endl;
         std::cout << "ft vector @ [10] : " << test_ft[10] << std::endl;
     
     
     
         // Testing iteration -----------------------------
         std::cout << "---------FT VECTOR----------------------" << std::endl;
         for(ft::vector<int>::iterator it_ft = test_ft.begin(); it_ft != test_ft.end(); ++it_ft) {
             std::cout << i++ << ": *it_ft: " << *it_ft << std::endl;
         }
         i = 0;
         std::cout << std::endl << "---------STD VECTOR----------------------" << std::endl;
         for(std::vector<int>::iterator it_std = test_std.begin(); it_std != test_std.end(); ++it_std) {
             std::cout << i++ << "*it_std: " << *it_std << std::endl;
         }
         // --------------------------------------------------
         std::cout << std::endl << "---------------Empty()--------------------------------" << std::endl;
         std::cout << "Is ft vector empty ? - " << test_ft.empty() << std::endl;
         std::cout << "Is std vector empty ? - " << test_std.empty() << std::endl;
         //---------------------------------------------------
         std::cout << std::endl << "---------------Capacity()--------------------------------" << std::endl;
         std::cout << "ft vector capacity : " << test_ft.capacity() << std::endl;
         std::cout << "std vector capacity : " << test_std.capacity() << std::endl;
         //---------------------------------------------------
         std::cout << std::endl << "---------------Max_size()--------------------------------" << std::endl;
         std::cout << "ft vector max_size : " << test_ft.max_size() << std::endl;
         std::cout << "std vector max_size : " << test_std.max_size() << std::endl;
         //---------------------------------------------------
         std::cout << std::endl << "---------------Size()--------------------------------" << std::endl;
         std::cout << "ft vector size : " << test_ft.size() << std::endl;
         std::cout << "std vector size : " << test_std.size() << std::endl;
         //---------------------------------------------------
         std::cout << std::endl << "---------------operator[]--------------------------------" << std::endl;
         std::cout << "ft vector @ [2] : " << test_ft[2] << std::endl;
         std::cout << "std vector @ [2] : " << test_std[2] << std::endl;
         //---------------------------------------------------
         std::cout << std::endl << "---------------at()--------------------------------" << std::endl;
         std::cout << "ft vector at 4 : " << test_ft.at(4) << std::endl;
         std::cout << "std vector at 4 : " << test_std.at(4) << std::endl;
         // DECOMMENT THESE ONE BY ONE TO CHECK THROW
         //test_ft.at(22);
         //test_std.at(22);
     
         //---------------------------------------------------
         std::cout << std::endl << "---------------front()--------------------------------" << std::endl;
         std::cout << "ft vector front : " << test_ft.front() << std::endl;
         std::cout << "std vector front : " << test_std.front() << std::endl;
         //---------------------------------------------------
         std::cout << std::endl << "---------------back()--------------------------------" << std::endl;
         std::cout << "ft vector back : " << test_ft.back() << std::endl;
         std::cout << "std vector back : " << test_std.back() << std::endl;
     
     
         return (0);*/
}

/*#include <iostream>
#include <string>
#include <deque>
#if 1 //CREATE A REAL STL EXAMPLE
#include <map>
#include <stack>
#include <vector>
namespace ft = std;
#else
#include <map.hpp>
	#include <stack.hpp>
	#include <vector.hpp>
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
    int idx;
    char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
    MutantStack() {}
    MutantStack(const MutantStack<T>& src) { *this = src; }
    MutantStack<T>& operator=(const MutantStack<T>& rhs)
    {
        this->c = rhs.c;
        return *this;
    }
    ~MutantStack() {}

    typedef typename ft::stack<T>::container_type::iterator iterator;

    iterator begin() { return this->c.begin(); }
    iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) {
    if (argc != 2)
    {
        std::cerr << "Usage: ./test seed" << std::endl;
        std::cerr << "Provide a seed please" << std::endl;
        std::cerr << "Count value:" << COUNT << std::endl;
        return 1;
    }
    const int seed = atoi(argv[1]);
    srand(seed);

    ft::vector<std::string> vector_str;
    ft::vector<int> vector_int;
    ft::stack<int> stack_int;
    ft::vector<Buffer> vector_buffer;
    ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
    ft::map<int, int> map_int;

    for (int i = 0; i < COUNT; i++)
    {
        vector_buffer.push_back(Buffer());
    }

    for (int i = 0; i < COUNT; i++)
    {
        const int idx = rand() % COUNT;
        vector_buffer[idx].idx = 5;
    }
    ft::vector<Buffer>().swap(vector_buffer);

    try
    {
        for (int i = 0; i < COUNT; i++)
        {
            const int idx = rand() % COUNT;
            vector_buffer.at(idx);
            std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
        }
    }
    catch(const std::exception& e)
    {
        //NORMAL ! :P
    }

    for (int i = 0; i < COUNT; ++i)
    {
        map_int.insert(ft::make_pair(rand(), rand()));
    }

    int sum = 0;
    for (int i = 0; i < 10000; i++)
    {
        int access = rand();
        sum += map_int[access];
    }
    std::cout << "should be constant with the same seed: " << sum << std::endl;

    {
        ft::map<int, int> copy = map_int;
    }
    MutantStack<char> iterable_stack;
    for (char letter = 'a'; letter <= 'z'; letter++)
        iterable_stack.push(letter);
    for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
    {
        std::cout << *it;
    }
    std::cout << std::endl;
    return (0);
}*/

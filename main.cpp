#include "srcs/vector.hpp"
#include <vector>

int main () {
    //int i = 0;
    ft::vector<int> test_ft(50, 100);
    std::vector<int> test_std(50, 100);

    /*std::cout << "--------------------push_back()---------------------------" << std::endl;
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

    */

    // Testing iteration -----------------------------
    /*std::cout << "---------FT VECTOR----------------------" << std::endl;
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

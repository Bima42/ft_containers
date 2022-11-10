# ft_containers
- [1. Get Started](#get-started)
- [2. Docs](#docs)
  - [2.1 Vector](#vector)
  - [2.2 Map](#map)
  - [2.3 Stack](#stack)
  - [2.4 Utils](#utils)
- [3. Testers](#testers) 

We have to build our own vector, map and stack.
We also have to implement some other STD tools, such as enable_if, iterator_traits, pair etc..

# Get Started
```
git clone git@github.com:Bima42/ft_containers.git
```

```
make
``` 

```
./containers
```

- Use the `--help` to display all possibilities

# Docs
- There is a non exhaustive list of docs that I used to do this project.
- [cplusplus](http://cplusplus.com) and [cppreference](http://cppreference.com) are just awesome for ft_containers. There is a lot to read.
- Be careful to check when functions were added to the container, some since C++11. You don't have to implement those.

## Vector
- [Vector and functions](https://cplusplus.com/reference/vector/vector/)
- [Others](https://en.cppreference.com/w/cpp/container/vector)
- C++11 functions :
  - cbegin(), cend(), crbegin(), crend()
  - shrink_to_fit()
  - emplace()
  - emplace_back()

## Map
- [Map and functions](https://cplusplus.com/reference/map/map)
- [Others](https://en.cppreference.com/w/cpp/container/map)
- [Old but great](https://www.cs.odu.edu/~zeil/cs361/latest/Directory/outline/)
- [Map docs](https://www.cs.odu.edu/~zeil/cs361/latest/Public/maps/index.html)
- [Binary Tree and Iterator](https://www.cs.odu.edu/~zeil/cs361/latest/Public/treetraversal/index.html)
- [BinarySearchTree.h](https://www.cs.odu.edu/~zeil/cs361/latest/Public/treetraversal/BSTwithIterator.h.html)
- [Others](https://en.cppreference.com/w/cpp/container/vector)
- C++11 functions :
  - cbegin(), cend(), crbegin(), crend()
  - emplace(), emplace_hint()
- C++17 and more :
  - insert_or_assign()
  - try_emplace()
  - extract()
  - merge()
  - contains()
  
## Stack
- [Stack and functions](https://cplusplus.com/reference/stack/stack/)
- [Others](https://en.cppreference.com/w/cpp/container/stack)
- C++11 functions :
  - emplace()
  - swap()

## Utils
- [std_allocator](https://en.cppreference.com/w/cpp/memory/allocator)
- [std_allocator](https://cplusplus.com/reference/memory/allocator/)
- [iterator](https://cplusplus.com/reference/iterator/iterator_traits/)
- [reverse_iterator](https://cplusplus.com/reference/iterator/reverse_iterator/reverse_iterator/)
- [enable_if](https://cplusplus.com/reference/type_traits/enable_if/)
- [enable_if](https://www.boost.org/doc/libs/1_39_0/libs/utility/enable_if.html)
- [is_integral](https://cplusplus.com/reference/type_traits/is_integral/)
- [source is_integral](https://code.woboq.org/appleseed/include/boost/type_traits/is_integral.hpp.html)
- [equal](https://cplusplus.com/reference/algorithm/equal/)
- [pair](https://en.cppreference.com/w/cpp/utility/pair)

# Testers
Thanks to [@divinepet](https://github.com/divinepet) and [@mli42](https://github.com/mli42)
- [Divinepet Tester](https://github.com/divinepet/ft_containers-unit-test)
- [Mli42 Tester](https://github.com/mli42/containers_test)

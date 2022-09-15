#include "../inc/tests_utils.hpp"

static double start1;
static double start2;
static double end1;
static double end2;

void tests_vector()
{
    std::cout <<
    "████████╗███████╗███████╗████████╗███████╗    ██╗   ██╗███████╗ ██████╗████████╗ ██████╗ ██████╗  \n"
    "╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝██╔════╝    ██║   ██║██╔════╝██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗ \n"
    "   ██║   █████╗  ███████╗   ██║   ███████╗    ██║   ██║█████╗  ██║        ██║   ██║   ██║██████╔╝ \n"
    "   ██║   ██╔══╝  ╚════██║   ██║   ╚════██║    ╚██╗ ██╔╝██╔══╝  ██║        ██║   ██║   ██║██╔══██╗ \n"
    "   ██║   ███████╗███████║   ██║   ███████║     ╚████╔╝ ███████╗╚██████╗   ██║   ╚██████╔╝██║  ██║ \n"
    "   ╚═╝   ╚══════╝╚══════╝   ╚═╝   ╚══════╝      ╚═══╝  ╚══════╝ ╚═════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝ " << std::endl;

    // Constructors tests
    {
        // ========= STD DECLARATIONS =====================
        _svec<int> std_test_void;
        _svec<int> std_test(10);
        _svec<int>::const_iterator it_std = std_test.begin();
        _svec<int>::const_iterator ite_std = --(--std_test.end());
        _svec<int> std_test2(std_test);
        _svec<int> std_test3(100, 99);
        _svec<int> std_test4(it_std, ite_std);
        // ========= FT DECLARATIONS =====================
        _fvec<int> ft_test_void;
        _fvec<int> ft_test(10);
        _fvec<int>::const_iterator it_ft = ft_test.begin();
        _fvec<int>::const_iterator ite_ft = --(--ft_test.end());
        _fvec<int> ft_test2(ft_test);
        _fvec<int> ft_test3(100, 99);
        _fvec<int> ft_test4(it_ft, ite_ft);
        // ========= COMPARISONS =========================
        std::cout << FMAG("============== Constructors comparisons ==============") << std::endl;
        std::cout << FGRN("void constructor :") << std::endl;
        std::cout << "-----------ft----------- " << std::endl;
        printSize(ft_test_void, 0);
        std::cout << "-----------std-----------" << std::endl;
        printSize(std_test_void, 0);
        std::cout << std::endl << std::endl;

        std::cout << FGRN("value constructor :") << std::endl;
        std::cout << "-----------ft----------- " << std::endl;
        printSize(ft_test, 0);
        std::cout << "-----------std-----------" << std::endl;
        printSize(std_test, 0);
        std::cout << FCYN("COMPARE CONTENT----------------------") << std::endl;
        controlContent(ft_test, std_test);
        std::cout << std::endl << std::endl;

        std::cout << FGRN("copy constructor :") << std::endl;
        std::cout << "-----------ft----------- " << std::endl;
        printSize(ft_test2, 0);
        std::cout << "-----------std-----------" << std::endl;
        printSize(std_test2, 0);
        std::cout << FCYN("COMPARE CONTENT----------------------") << std::endl;
        controlContent(ft_test2, std_test2);
        std::cout << std::endl << std::endl;

        std::cout << FGRN("value and fill constructor :") << std::endl;
        std::cout << "-----------ft----------- " << std::endl;
        printSize(ft_test3, 0);
        std::cout << "-----------std-----------" << std::endl;
        printSize(std_test3, 0);
        std::cout << FCYN("COMPARE CONTENT----------------------") << std::endl;
        controlContent(ft_test3, std_test3);
        std::cout << std::endl << std::endl;

        std::cout << FGRN("iterator range constructor :") << std::endl;
        std::cout << "-----------ft----------- " << std::endl;
        printSize(ft_test4, 0);
        std::cout << "-----------std-----------" << std::endl;
        printSize(std_test4, 0);

        std::cout << FCYN("COMPARE CONTENT----------------------") << std::endl;
        controlContent(ft_test4, std_test4);
        std::cout << std::endl << std::endl;
    }

    {
        std::cout << FMAG("============== assign() ==============") << std::endl;
        // ========= STD DECLARATIONS =====================
        _svec<int> std_test(10);


        // ========= FT DECLARATIONS =====================
        _fvec<int> ft_test(10);


        // ========= COMPARISONS =========================
        std::cout << FGRN("Assign fill :") << std::endl;

        std::cout << "-----------ft----------- " << std::endl;
        start1 = std::clock();
        ft_test.assign(250, 100);
        end1 = std::clock();
        printSize(ft_test, 0);

        std::cout << "-----------std-----------" << std::endl;
        start2 = std::clock();
        std_test.assign(250, 100);
        end2 = std::clock();
        printSize(std_test, 0);

        std::string toPrint;
        double time = (end2 - start2) == 0 ? 1 : (end2 - start2);
        toPrint = ((end1 - start1) > (time * 20)) ? FRED("Diff Time KO") : FGRN("Diff Time OK");
        std::cout << toPrint << std::endl << std::endl;

        // CREATING ITERATORS ==================================
        _fvec<int>::const_iterator it_ft = ft_test.begin();
        _fvec<int>::const_iterator it2_ft = ft_test.begin();

        _svec<int>::const_iterator it_std = std_test.begin();
        _svec<int>::const_iterator it2_std = std_test.begin();

        for (int i = 0; i < 10; i++)
            it2_ft++;
        for (int i = 0; i < 10; i++)
            it2_std++;
        // ======================================================

        std::cout << FGRN("Assign range :") << std::endl;

        start1 = std::clock();
        ft_test.assign(it_ft, it2_ft);
        end1 = std::clock();

        std::cout << "-----------ft----------- " << std::endl;
        printSize(ft_test, 0);
        std::cout << "-----------std-----------" << std::endl;

        start2 = std::clock();
        std_test.assign(it_std, it2_std);
        end2 = std::clock();

        printSize(std_test, 0);
        std::cout << std::endl;

        std::cout << FCYN("COMPARE CONTENT----------------------") << std::endl;
        controlContent(ft_test, std_test);

        time = (end2 - start2) == 0 ? 1 : (end2 - start2);
        toPrint = ((end1 - start1) > (time * 20)) ? FRED("Diff Time KO") : FGRN("Diff Time OK");
        std::cout << toPrint << std::endl << std::endl;
    }
    {
        std::cout << FMAG("============== at() ==============") << std::endl;
        // ========= STD DECLARATIONS =====================
        _svec<int> std_test(200, 200);
        _svec<int>::iterator it_std = std_test.begin();
        for (int i = 0; i < 100; i++)
            it_std++;
        std_test.insert(it_std, 42);
        // ========= FT DECLARATIONS =====================
        _fvec<int> ft_test(200, 200);
        _fvec<int>::iterator it_ft = ft_test.begin();
        for (int i = 0; i < 100; i++)
            it_ft++;
        ft_test.insert(it_ft, 42);
        // ========= COMPARISONS =========================
        std::cout << FGRN("assign check :") << std::endl;
        start1 = std::clock();
        std::cout << "-----------ft----------- " << std::endl;
        std::cout << "99: " << ft_test.at(99) << " | 100: " << ft_test.at(100)
                  << " | 101: " << ft_test.at(101) << std::endl;
        end1 = std::clock();

        std::cout << "-----------std----------- " << std::endl;
        start2 = std::clock();
        std::cout << "99: " << std_test.at(99) << " | 100: " << std_test.at(100)
                  << " | 101: " << std_test.at(101) << std::endl;
        end2 = std::clock();

        std::cout << FCYN("COMPARE CONTENT----------------------") << std::endl;
        controlContent(ft_test, std_test);

        std::string toPrint;
        double time = (end2 - start2) == 0 ? 1 : (end2 - start2);
        toPrint = ((end1 - start1) > (time * 20)) ? FRED("Diff Time KO") : FGRN("Diff Time OK");
        std::cout << toPrint << std::endl << std::endl;
    }

    {
        std::cout << FMAG("============== erase() ==============") << std::endl;
        // ========= STD DECLARATIONS =====================
        _svec<int> std_test(200, 200);
        _svec<int>::iterator it_std = std_test.begin();
        _svec<int>::iterator ite_std = --(--std_test.end());
        for (int i = 0; i < 100; i++)
            it_std++;
        // ========= FT DECLARATIONS =====================
        _fvec<int> ft_test(200, 200);
        _fvec<int>::iterator it_ft = ft_test.begin();
        _fvec<int>::iterator ite_ft = --(--ft_test.end());
        for (int i = 0; i < 100; i++)
            it_ft++;
        // ========= COMPARISONS =========================
        std::cout << FGRN("erase position :") << std::endl;
        std::cout << "-----------ft----------- " << std::endl;
        std::cout << "Before erase :" << std::endl;
        printSize(ft_test, 0);
        std::cout << "After erase :" << std::endl;

        start1 = std::clock();
        ft_test.erase(it_ft);
        end1 = std::clock();

        printSize(ft_test, 0);
        std::cout << "-----------std----------- " << std::endl;
        std::cout << "Before erase :" << std::endl;
        printSize(std_test, 0);
        std::cout << "After erase :" << std::endl;

        start2 = std::clock();
        std_test.erase(it_std);
        end2 = std::clock();

        printSize(std_test, 0);

        std::string toPrint;
        double time = (end2 - start2) == 0 ? 1 : (end2 - start2);
        toPrint = ((end1 - start1) > (time * 20)) ? FRED("Diff Time KO") : FGRN("Diff Time OK");
        std::cout << toPrint << std::endl << std::endl;

        std::cout << FGRN("erase range :") << std::endl;
        std::cout << "-----------ft----------- " << std::endl;
        std::cout << "Before erase :" << std::endl;
        printSize(ft_test, 0);
        std::cout << "After erase :" << std::endl;

        start1 = std::clock();
        ft_test.erase(ft_test.begin(), ite_ft);
        end1 = std::clock();

        printSize(ft_test, 0);
        std::cout << "-----------std----------- " << std::endl;
        std::cout << "Before erase :" << std::endl;
        printSize(std_test, 0);
        std::cout << "After erase :" << std::endl;

        start2 = std::clock();
        std_test.erase(std_test.begin(), ite_std);
        end2 = std::clock();

        printSize(std_test, 0);

        std::cout << FCYN("COMPARE CONTENT----------------------") << std::endl;
        controlContent(ft_test, std_test);

        time = (end2 - start2) == 0 ? 1 : (end2 - start2);
        toPrint = ((end1 - start1) > (time * 20)) ? FRED("Diff Time KO") : FGRN("Diff Time OK");
        std::cout << toPrint << std::endl << std::endl;
    }
    {
        std::cout << FMAG("============== insert() ==============") << std::endl;
        // ========= STD DECLARATIONS =====================
        _svec<int> std_test(200, 200);
        _svec<int>::iterator it_std = std_test.begin();
        for (int i = 0; i < 100; i++)
            it_std++;
        // ========= FT DECLARATIONS =====================
        _fvec<int> ft_test(200, 200);
        _fvec<int>::iterator it_ft = ft_test.begin();
        for (int i = 0; i < 100; i++)
            it_ft++;
        // ========= COMPARISONS =========================
        std::cout << FGRN("insert val @ position :") << std::endl;
        std::cout << "-----------ft----------- " << std::endl;
        std::cout << "Before insert of 42 @ position 100 :" << std::endl;
        printSize(ft_test, 0);
        std::cout << "After insert of 42 @ position 100 :" << std::endl;
        it_ft = ft_test.insert(it_ft, 42);
        printSize(ft_test, 0);
        std::cout << "-----------std----------- " << std::endl;
        std::cout << "Before insert of 42 @ position 100 :" << std::endl;
        printSize(std_test, 0);
        std::cout << "After insert of 42 @ position 100 :" << std::endl;
        it_std = std_test.insert(it_std, 42);
        printSize(std_test, 0);
        std::cout << std::endl;

        std::cout << FGRN("insert range :") << std::endl;
        std::cout << "-----------ft----------- " << std::endl;
        std::cout << "Before inserting range of begin to end @ position 100 :" << std::endl;
        printSize(ft_test, 0);
        std::cout << "After inserting range of begin to end @ position 100 :" << std::endl;
        ft_test.insert(it_ft, ft_test.begin(), ft_test.end());
        printSize(ft_test, 0);
        std::cout << "-----------std----------- " << std::endl;
        std::cout << "Before inserting range of begin to end @ position 100 :" << std::endl;
        printSize(std_test, 0);
        std::cout << "After inserting range of begin to end @ position 100 :" << std::endl;
        std_test.insert(it_std, std_test.begin(), std_test.end());
        printSize(std_test, 0);
        std::cout << std::endl;

        std::cout << FGRN("insert pos n' fill :") << std::endl;
        std::cout << "-----------ft----------- " << std::endl;
        std::cout << "Before inserting 300 times 42 on begin:" << std::endl;
        printSize(ft_test, 0);
        std::cout << "After inserting 300 times 42 on begin:" << std::endl;
        ft_test.insert(ft_test.begin(), 300, 42);
        printSize(ft_test, 0);
        std::cout << "-----------std----------- " << std::endl;
        std::cout << "Before inserting 300 times 42 on begin:" << std::endl;
        printSize(std_test, 0);
        std::cout << "After inserting 300 times 42 on begin:" << std::endl;
        std_test.insert(std_test.begin(), 300, 42);
        printSize(std_test, 0);

        std::cout << FCYN("COMPARE CONTENT----------------------") << std::endl;
        controlContent(ft_test, std_test);
        std::cout << std::endl << std::endl;
    }

    {
        std::cout << FMAG("============== pop_back() ==============") << std::endl;
        // ========= STD DECLARATIONS =====================
        _svec<int> std_test(200, 200);
        // ========= FT DECLARATIONS =====================
        _fvec<int> ft_test(200, 200);
        // ========= COMPARISONS =========================
        std::cout << FGRN("pop_back once") << std::endl;
        std::cout << "-----------ft----------- " << std::endl;
        std::cout << "Before :" << std::endl;
        printSize(ft_test, 0);
        std::cout << "After :" << std::endl;
        ft_test.pop_back();
        printSize(ft_test, 0);
        std::cout << "-----------std----------- " << std::endl;
        std::cout << "Before :" << std::endl;
        printSize(std_test, 0);
        std::cout << "After :" << std::endl;
        std_test.pop_back();
        printSize(std_test, 0);
        std::cout << FCYN("COMPARE CONTENT----------------------") << std::endl;
        controlContent(ft_test, std_test);
        std::cout << std::endl << std::endl;
    }

    {
        std::cout << FMAG("============== push_back() ==============") << std::endl;
        // ========= STD DECLARATIONS =====================
        _svec<int> std_test(200, 200);
        // ========= FT DECLARATIONS =====================
        _fvec<int> ft_test(200, 200);
        // ========= COMPARISONS =========================
        std::cout << FGRN("push_back once") << std::endl;
        std::cout << "-----------ft----------- " << std::endl;
        std::cout << "Before :" << std::endl;
        printSize(ft_test, 0);
        std::cout << "After :" << std::endl;
        ft_test.push_back(10);
        printSize(ft_test, 0);
        std::cout << "-----------std----------- " << std::endl;
        std::cout << "Before :" << std::endl;
        printSize(std_test, 0);
        std::cout << "After :" << std::endl;
        std_test.push_back(10);
        printSize(std_test, 0);
        std::cout << FCYN("COMPARE CONTENT----------------------") << std::endl;
        controlContent(ft_test, std_test);
        std::cout << std::endl << std::endl;

        std::cout << FMAG("============== resize() ==============") << std::endl;
        std::cout << FGRN("resize 12") << std::endl;
        std::cout << "-----------ft----------- " << std::endl;
        std::cout << "Before :" << std::endl;
        printSize(ft_test, 0);
        std::cout << "After :" << std::endl;
        ft_test.resize(12);
        printSize(ft_test, 0);
        std::cout << "-----------std----------- " << std::endl;
        std::cout << "Before :" << std::endl;
        printSize(std_test, 0);
        std::cout << "After :" << std::endl;
        std_test.resize(12);
        printSize(std_test, 0);
        std::cout << std::endl;
        std::cout << FGRN("resize 4000") << std::endl;
        ft_test.resize(4000);
        printSize(ft_test, 0);
        std_test.resize(4000);
        printSize(std_test, 0);

        std::cout << FCYN("COMPARE CONTENT----------------------") << std::endl;
        controlContent(ft_test, std_test);
        std::cout << std::endl << std::endl;
    }

    {
        std::cout << FMAG("============== shrink_to_fit() ==============") << std::endl;
        // ========= STD DECLARATIONS =====================
        _svec<int> std_test(200, 200);
        std_test.reserve(4242);
        // ========= FT DECLARATIONS =====================
        _fvec<int> ft_test(200, 200);
        ft_test.reserve(4242);
        // ========= COMPARISONS =========================
        std::cout << FGRN("shrink to fit the current size") << std::endl;
        std::cout << "-----------ft----------- " << std::endl;
        std::cout << "Before :" << std::endl;
        printSize(ft_test, 0);
        std::cout << "After :" << std::endl;
        ft_test.shrink_to_fit();
        printSize(ft_test, 0);
        std::cout << "-----------std----------- " << std::endl;
        std::cout << "Before :" << std::endl;
        printSize(std_test, 0);
        std::cout << "After :" << std::endl;
        std_test.shrink_to_fit();
        printSize(std_test, 0);

        std::cout << FCYN("COMPARE CONTENT----------------------") << std::endl;
        controlContent(ft_test, std_test);
        std::cout << std::endl << std::endl;
    }
    {
        std::cout << FMAG("============== swap() ==============") << std::endl;
        // ========= STD DECLARATIONS =====================
        _svec<int> std_test(200, 200);
        _svec<int> std_swap(2000, 100);
        // ========= FT DECLARATIONS =====================
        _fvec<int> ft_test(200, 200);
        _fvec<int> ft_swap(2000, 100);
        // ========= COMPARISONS =========================
        std::cout << FGRN("swapping the vector with another one") << std::endl;
        std::cout << "-----------ft----------- " << std::endl;
        std::cout << "Before :" << std::endl;
        printSize(ft_test, 0);
        std::cout << "After :" << std::endl;
        ft_test.swap(ft_swap);
        printSize(ft_test, 0);
        std::cout << "-----------std----------- " << std::endl;
        std::cout << "Before :" << std::endl;
        printSize(std_test, 0);
        std::cout << "After :" << std::endl;
        std_test.swap(std_swap);
        printSize(std_test, 0);

        std::cout << FCYN("COMPARE CONTENT----------------------") << std::endl;
        std::cout << "Content of the originals vectors" << std::endl;
        controlContent(ft_test, std_test);
        std::cout << "Content of the swapped vectors" << std::endl;
        controlContent(ft_swap, std_swap);
        std::cout << std::endl << std::endl;
    }

    {
        std::cout << FMAG("============== relational operators ==============") << std::endl;
        // ========= STD DECLARATIONS =====================

        // ========= FT DECLARATIONS =====================
        ft::vector<int> vct(4);
        ft::vector<int> vct2(4);

        // ========= COMPARISONS =========================
        std::cout << FGRN(" ----- Infos of vct1 ----- ") << std::endl;
        printSize(vct, 1);
        std::cout << std::endl << FGRN(" ----- Infos of vct2 ----- ") << std::endl;
        printSize(vct2, 1);


        cmp(vct, vct);  // 0
        cmp(vct, vct2); // 1

        std::cout << "-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << std::endl;
        vct2.resize(10);
        std::cout << FGRN(" ----- Infos of vct1 ----- ") << std::endl;
        printSize(vct, 1);
        std::cout << std::endl << FGRN(" ----- Infos of vct2 ----- ") << std::endl;
        printSize(vct2, 1);

        cmp(vct, vct2); // 2
        cmp(vct2, vct); // 3

        std::cout << "-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << std::endl;
        vct[2] = 42;
        std::cout << FGRN(" ----- Infos of vct1 ----- ") << std::endl;
        printSize(vct, 1);
        std::cout << std::endl << FGRN(" ----- Infos of vct2 ----- ") << std::endl;
        printSize(vct2, 1);

        cmp(vct, vct2); // 4
        cmp(vct2, vct); // 5

        std::cout << "-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << std::endl;
        swap(vct, vct2);
        std::cout << FGRN(" ----- Infos of vct1 ----- ") << std::endl;
        printSize(vct, 1);
        std::cout << std::endl << FGRN(" ----- Infos of vct2 ----- ") << std::endl;
        printSize(vct2, 1);

        cmp(vct, vct2); // 6
        cmp(vct2, vct); // 7
    }

    {
        const int size = 10;
        ft::vector<int> vct(size);
        ft::vector<int>::iterator it_ = vct.end();
        ft::vector<int>::reverse_iterator rit(it_);

        for (int i = 0; i < size; ++i)
            vct[i] = i;
        printSize(vct, 1);

        std::cout << std::endl;
        std::cout << "reverse iterator post and pre increment" << std::endl;
        ++rit;
        std::cout << "++reverse iterator : " << *rit << std::endl;
        rit++;
        std::cout << "reverse iterator++ : " << *rit << std::endl;
        --rit;
        std::cout << "--reverse iterator : " << *rit << std::endl;
        rit--;
        std::cout << "reverse iterator-- : " << *rit << std::endl;
        rit += 4;
        std::cout << "reverse iterator + 4 : " << *rit << std::endl;
        rit -= 2;
        std::cout << "reverse iterator + 2: " << *rit << std::endl << std::endl;

    }
}

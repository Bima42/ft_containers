#include "tests_utils.hpp"

static double start1;
static double start2;
static double end1;
static double end2;

void tests_map()
{
    std::cout
    << "████████╗███████╗███████╗████████╗███████╗    ███╗   ███╗ █████╗ ██████╗  \n"
    << "╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝██╔════╝    ████╗ ████║██╔══██╗██╔══██╗ \n"
    << "   ██║   █████╗  ███████╗   ██║   ███████╗    ██╔████╔██║███████║██████╔╝ \n"
    << "   ██║   ██╔══╝  ╚════██║   ██║   ╚════██║    ██║╚██╔╝██║██╔══██║██╔═══╝  \n"
    << "   ██║   ███████╗███████║   ██║   ███████║    ██║ ╚═╝ ██║██║  ██║██║      \n"
    << "   ╚═╝   ╚══════╝╚══════╝   ╚═╝   ╚══════╝    ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝      " << std::endl;
    {
        std::cout << "######### Constructors ###########" << std::endl;

        std::list<FT3> lst;
        unsigned int lst_size = 100;
        for (unsigned int i = 0; i < lst_size; ++i)
            lst.push_back(FT3(lst_size - i, i));

        start1 = std::clock(); //timer
        _ft<T1, T2> mp_ft(lst.begin(), lst.end());
        _ft<T1, T2>::iterator it_ft = mp_ft.begin(), ite_ft = --(--mp_ft.end());

        _ft<T1, T2> mp_copy_ft(mp_ft);
        for (int i = 0; it_ft != ite_ft; ++it_ft)
            it_ft->second = ++i * 7;
        _ft<T1, T2> mp_equal_ft = mp_ft;
        end1 = std::clock(); //end

        start2 = std::clock(); //timer
        std::list<STD3> lst2;
        for (unsigned int i = 0; i < lst_size; ++i)
            lst2.push_back(STD3(lst_size - i, i));

        _std<T1, T2> mp_std(lst2.begin(), lst2.end());
        _std<T1, T2>::iterator it_std = mp_std.begin(), ite_std = --(--mp_std.end());

        _std<T1, T2> mp_copy_std(mp_std);
        for (int i = 0; it_std != ite_std; ++it_std)
            it_std->second = ++i * 7;
        _std<T1, T2> mp_equal_std = mp_std;
        end2 = std::clock(); //end

        std::cout << "Range -> ";
        controlSize(mp_ft, mp_std);
        std::cout << "Copy -> ";
        controlSize(mp_copy_ft, mp_copy_std);
        std::cout << "Overload Assignment -> ";
        controlSize(mp_equal_ft, mp_equal_std);

        int i = -1;
        std::string toPrint;
        while (++i < 100)
        {
            if (mp_ft[i] != mp_std[i]
                || mp_copy_ft[i] != mp_copy_std[i]
                || mp_equal_ft[i] != mp_equal_std[i])
                break;
        }
        toPrint = (i != 100) ? "Content : KO" : "Content : OK";
        std::cout << toPrint << std::endl;

        double time = (end2 - start2) == 0 ? 1 : (end2 - start2);
        toPrint = ((end1 - start1) > (time * 20)) ? FRED("Diff Time KO") : FGRN("Diff Time OK");
        std::cout << toPrint << std::endl << std::endl;
    }
    {
        std::cout << "############ Bounds ##############" << std::endl;

        std::list<FT3> lst;
        unsigned int lst_size = 10;
        for (unsigned int i = 0; i < lst_size; ++i)
            lst.push_back(FT3(i + 1, (i + 1) * 3));
        _ft<T1, T2> mp_ft(lst.begin(), lst.end());

        std::list<STD3> lst2;
        for (unsigned int i = 0; i < lst_size; ++i)
            lst2.push_back(STD3(i + 1, (i + 1) * 3));
        _std<T1, T2> mp_std(lst2.begin(), lst2.end());

        start1 = std::clock();
        _ft_it fit1 = mp_ft.lower_bound(1);
        _ft_it fit2 = mp_ft.upper_bound(1);
        _ft_pair<_ft_it, _ft_it> fit3 = mp_ft.equal_range(1);
        end1 = std::clock();

        start1 = std::clock();
        _std_it sit1 = mp_std.lower_bound(1);
        _std_it sit2 = mp_std.upper_bound(1);
        _std_pair<_std_it, _std_it> sit3 = mp_std.equal_range(1);
        end1 = std::clock();

        std::string toPrint;

        toPrint = (fit1->first == sit1->first && fit1->second == sit1->second) ? "Lower bound : ✅" : "Lower bound : ❌";
        std::cout << toPrint << std::endl;
        toPrint = (fit2->first == sit2->first && fit2->second == sit2->second) ? "Upper bound : ✅" : "Upper bound : ❌";
        std::cout << toPrint << std::endl;
        toPrint = (fit3.first->first == sit3.first->first && fit3.first->second == sit3.first->second
                    && fit3.second->first == sit3.second->first && fit3.second->second == sit3.second->second) ? "Equal range : ✅" : "Upper bound : ❌";
        std::cout << toPrint << std::endl;

        double time = (end2 - start2) == 0 ? 1 : (end2 - start2);
        toPrint = ((end1 - start1) > (time * 20)) ? FRED("Diff Time KO") : FGRN("Diff Time OK");
        std::cout << toPrint << std::endl << std::endl;
    }
    {
        std::cout << "############ Empty ###############" << std::endl;

        _ft<T1, T2> mp_ft, mp_ft2;
        _std<T1, T2> mp_std, mp_std2;
        bool ret[4];

        mp_ft2['a'] = 40;
        mp_std2['a'] = 40;

        start1 = std::clock();
        ret[0] = mp_ft.empty();
        ret[1] = mp_ft2.empty();
        end1 = std::clock();

        start2 = std::clock();
        ret[2] = mp_std.empty();
        ret[3] = mp_std2.empty();
        end2 = std::clock();

        std::string toPrint;

        toPrint = (ret[0] == ret[2]) ? "Empty : ✅" : "Empty : ❌";
        std::cout << "Map empty -> " << toPrint << std::endl;
        toPrint = (ret[1] == ret[3]) ? "Empty : ✅" : "Empty : ❌";
        std::cout << "Map fill -> " << toPrint << std::endl;

        double time = (end2 - start2) == 0 ? 1 : (end2 - start2);
        toPrint = ((end1 - start1) > (time * 20)) ? FRED("Diff Time KO") : FGRN("Diff Time OK");
        std::cout << toPrint << std::endl << std::endl;
    }
    {
        std::cout << "############ Comp ################" << std::endl;

        _ft<T1, T2> mp_ft;
        _std<T1, T2> mp_std;
        std::string toPrint;

        for (unsigned int i = 1; i < 7; ++i) {
            mp_ft[i] = i * 10 + i;
            mp_std[i] = i * 10 + i;
        }

        int p = 6;
        int q = 60;
        _ft_pair<T1, T2> highest = ft::make_pair(p, q);
        _std_pair<T1, T2> highest2 = std::make_pair(p, q);

        _ft_it it = mp_ft.begin();
        _std_it sit = mp_std.begin();

        start1 = std::clock();
        while (mp_ft.value_comp()(*it, highest) == true)
        {
            std::cout << "FT : " << it->first << " => " << it->second
                    << " compare with " << highest.first << " => " << highest.second << std::endl;
            it++;
        }
        end1 = std::clock();

        start2 = std::clock();
        while (mp_std.value_comp()(*sit, highest2) == true)
        {
            std::cout << "STD : " << sit->first << " => " << sit->second
                    << " compare with " << highest2.first << " => " << highest2.second << std::endl;
            sit++;
        }
        end2 = std::clock();

        toPrint = (it->first == highest.first && sit->first == highest2.first) ? "Comp : ✅" : "Comp : ❌";
        std::cout << toPrint << std::endl;

        double time = (end2 - start2) == 0 ? 1 : (end2 - start2);
        toPrint = ((end1 - start1) > (time * 20)) ? FRED("Diff Time KO") : FGRN("Diff Time OK");
        std::cout << toPrint << std::endl << std::endl;
    }
    {
        std::cout << "############ Find ################" << std::endl;
        
        _ft<T4, T1> mp_ft;
        _ft<T4, T1>::iterator fit;

        _std<T4, T1> mp_std;
        _std<T4, T1>::iterator sit;

        mp_ft['a'] = 50;
        mp_ft['b'] = 100;
        mp_ft['c'] = 150;
        mp_ft['d'] = 200;

        mp_std['a'] = 50;
        mp_std['b'] = 100;
        mp_std['c'] = 150;
        mp_std['d'] = 200;

        start1 = std::clock();
        fit = mp_ft.find('b');
        std::cout << "FT -> Find b : " << fit->second << std::endl;
        end1 = std::clock();

        start2 = std::clock();
        sit = mp_std.find('b');
        std::cout << "STD -> Find b : " << sit->second << std::endl;
        end2 = std::clock();

        std::string toPrint;
        toPrint = (fit->second == sit->second) ? "Find : ✅" : "Find : ❌";
        std::cout << toPrint << std::endl;

        double time = (end2 - start2) == 0 ? 1 : (end2 - start2);
        toPrint = ((end1 - start1) > (time * 20)) ? FRED("Diff Time KO") : FGRN("Diff Time OK");
        std::cout << toPrint << std::endl << std::endl;
    }
    {
        std::cout << "########## Insert Value ###########" << std::endl;

        _ft<T1, T2> mp_ft;
        _ft<T1, T2>::iterator fit;

        start1 = std::clock();
        for (int i = 0; i < 1000; i++) {
            mp_ft.insert(ft::make_pair(i, i * 10));
        }
        _ft_pair<_ft_it, T2> ft_pair = mp_ft.insert(ft::make_pair(4, -444));
        end1 = std::clock();

        _std<T1, T2> mp_std;
        _std<T1, T2>::iterator sit;

        start2 = std::clock();
        for (int i = 0; i < 1000; i++) {
            mp_std.insert(STD3(i, i * 10));
        }
        _std_pair<_std_it, T2> std_pair = mp_std.insert(std::make_pair(4, -444));
        end2 = std::clock();

        std::string toPrint;
        std::cout << "Insert value -> ";
        controlSize(mp_ft, mp_std);

        std::cout << "Insert value -> ";
        toPrint = (ft_pair.second == std_pair.second) ? "Data inserted : ✅" : "Data inserted : ❌";
        std::cout << toPrint << std::endl;

        int i = -1;
        while (++i < 1000)
            if (mp_ft[i] != mp_std[i])
                break;
        toPrint = (i == 1000) ? "Content : ✅" : "Content : ❌";
        std::cout << toPrint << std::endl;

        double time = (end2 - start2) == 0 ? 1 : (end2 - start2);
        toPrint = ((end1 - start1) > (time * 20)) ? FRED("Diff Time KO") : FGRN("Diff Time OK");
        std::cout << toPrint << std::endl << std::endl;

        std::cout << "########## Insert Range ###########" << std::endl;
        
        start1 = std::clock();
        _ft<T1, T2> mp_ft_range;
        mp_ft_range.insert(mp_ft.begin(), mp_ft.find(400));
        end1 = std::clock();

        start2 = std::clock();
        _std<T1, T2> mp_std_range;
        mp_std_range.insert(mp_std.begin(), mp_std.find(400));
        end2 = std::clock();

        std::cout << "Insert range -> ";
        controlSize(mp_ft_range, mp_std_range);
        i = -1;
        while (++i < 400)
            if (mp_ft_range[i] != mp_std_range[i])
                break;
        toPrint = (i == 400) ? "Content : ✅\nData inserted : ✅" : "Content : ❌\nData inserted : ❌";
        std::cout << toPrint << std::endl;

        time = (end2 - start2) == 0 ? 1 : (end2 - start2);
        toPrint = ((end1 - start1) > (time * 20)) ? FRED("Diff Time KO") : FGRN("Diff Time OK");
        std::cout << toPrint << std::endl << std::endl;

        std::cout << "######### Insert Position #########" << std::endl;

        start1 = std::clock();
        _ft_it ret = mp_ft.insert(mp_ft.begin(), ft::make_pair(12, -444));
        end1 = std::clock();

        start2 = std::clock();
        _std_it ret2 = mp_std.insert(mp_std.begin(), std::make_pair(12, -444));
        end2 = std::clock();

        std::cout << "Insert position -> ";
        controlSize(mp_ft, mp_std);
        i = -1;
        while (++i < 1000)
            if (mp_ft[i] != mp_std[i])
                break;
        toPrint = (i == 1000) ? "Content : ✅" : "Content : ❌";
        std::cout << toPrint << std::endl;

        toPrint = ((*ret).second == (*ret2).second) ? "Data inserted ✅" : "Data inserted : ❌";
        std::cout << toPrint << std::endl;

        time = (end2 - start2) == 0 ? 1 : (end2 - start2);
        toPrint = ((end1 - start1) > (time * 20)) ? FRED("Diff Time KO") : FGRN("Diff Time OK");
        std::cout << toPrint << std::endl << std::endl;
    }
    {
        std::cout << "######## Erase position #########" << std::endl;

        _ft<T1, T2> mp_ft;
        for (int i = 0; i < 1000; i++)
            mp_ft.insert(FT3(i, i * 10));
        _ft_it it = mp_ft.begin();
        for (int i = 0; i < 200; i++)
            it++;

        start1 = std::clock();
        mp_ft.erase(it);
        end1 = std::clock();

        _std<T1, T2> mp_std;
        for (int i = 0; i < 1000; i++)
            mp_std.insert(STD3(i, i * 10));
        _std_it sit = mp_std.begin();
        for (int i = 0; i < 200; i++)
            sit++;

        start2 = std::clock();
        mp_std.erase(sit);
        end2 = std::clock();

        std::string toPrint;
        std::cout << "Erase position -> ";
        controlSize(mp_ft, mp_std);
        int i = -1;
        while (++i < 999)
            if (mp_ft[i] != mp_std[i])
                break;
        toPrint = (i == 999) ? "Content : ✅" : "Content : ❌";
        std::cout << toPrint << std::endl;

        double time = (end2 - start2) == 0 ? 1 : (end2 - start2);
        toPrint = ((end1 - start1) > (time * 20)) ? FRED("Diff Time KO") : FGRN("Diff Time OK");
        std::cout << toPrint << std::endl << std::endl;

        std::cout << "########## Erase key ###########" << std::endl;

        start1 = std::clock();
        mp_ft.erase(733);
        mp_ft.erase(800);
        end1 = std::clock();

        start2 = std::clock();
        mp_std.erase(733);
        mp_std.erase(800);
        end2 = std::clock();

        std::cout << "Erase key -> ";
        controlSize(mp_ft, mp_std);
        i = -1;
        while (++i < 997)
            if (mp_ft[i] != mp_std[i])
                break;
        toPrint = (i == 997) ? "Content : ✅" : "Content : ❌";
        std::cout << toPrint << std::endl;

        time = (end2 - start2) == 0 ? 1 : (end2 - start2);
        toPrint = ((end1 - start1) > (time * 20)) ? FRED("Diff Time KO") : FGRN("Diff Time OK");
        std::cout << toPrint << std::endl << std::endl;
    }
    {
        std::cout << "####### Iter - Rev Iter ########" << std::endl;

        _ft<T1, T2> mp_ft;
        for (int i = 0; i < 10; i++)
            mp_ft.insert(FT3(i, i));
        _ft_it it = mp_ft.begin();
        _ft_it it2 = mp_ft.begin();
        _ft_rit rit = mp_ft.rend();
        _ft_rit rit2 = mp_ft.rbegin();

        _std<T1, T2> mp_std;
        for (int i = 0; i < 10; i++)
            mp_std.insert(STD3(i, i));
        _std_it sit = mp_std.begin();
        _std_it sit2 = mp_std.begin();
        _std_rit rsit = mp_std.rend();
        _std_rit rsit2 = mp_std.rbegin();

        start1 = std::clock();
        for (int i = 0; i != 3; i++){
            ++it;
            --rit;
        }
        it2++;
        it2--;
        rit2++;
        end1 = std::clock();

        start1 = std::clock();
        for (int i = 0; i != 3; i++){
            ++sit;
            --rsit;
        }
        sit2++;
        sit2--;
        rsit2++;
        end2 = std::clock();

        std::string toPrint;
        toPrint = ((*it).first == (*sit).first) ? "Iter Increment : ✅" : "Iter Increment : ❌";
        std::cout << toPrint << std::endl;

        toPrint = ((*it2).first == (*sit2).first) ? "Iter Decrement : ✅" : "Iter Decrement : ❌";
        std::cout << toPrint << std::endl;

        toPrint = ((*rit).first == (*rsit).first) ? "Rev Iter Decrement : ✅" : "Rev Iter Decrement : ❌";
        std::cout << toPrint << std::endl;

        toPrint = ((*rit2).first == (*rsit2).first) ? "Rev Iter Increment : ✅" : "Rev Iter Increment : ❌";
        std::cout << toPrint << std::endl;

        double time = (end2 - start2) == 0 ? 1 : (end2 - start2);
        toPrint = ((end1 - start1) > (time * 20)) ? FRED("Diff Time KO") : FGRN("Diff Time OK");
        std::cout << toPrint << std::endl << std::endl;
    }
    {
        std::cout << "########## Swap ###########" << std::endl;

        _ft<T1, T2> mp_ft;
        _ft<T1, T2> mp_ft2;
        for (int i = 0; i < 5; i++)
            mp_ft.insert(FT3(i, i));
        for (int i = 7; i > 0; i--)
            mp_ft2.insert(FT3(i, i));
        
        std::cout << "---- FT Before swap ----" << std::endl;
        std::cout << "--------- Map1 ---------" << std::endl;
        printSizeMap(mp_ft);
        std::cout << "--------- Map2 ---------" << std::endl;
        printSizeMap(mp_ft2);

        start1 = std::clock();
        mp_ft.swap(mp_ft2);
        end1 = std::clock();

        std::cout << "---- FT After swap ----" << std::endl;
        std::cout << "--------- Map1 ---------" << std::endl;
        printSizeMap(mp_ft);
        std::cout << "--------- Map2 ---------" << std::endl;
        printSizeMap(mp_ft2);

        _std<T1, T2> mp_std;
        _std<T1, T2> mp_std2;
        for (int i = 0; i < 5; i++)
            mp_std.insert(STD3(i, i));
        for (int i = 7; i > 0; i--)
            mp_std2.insert(STD3(i, i));

        std::cout << "---- STD Before swap ----" << std::endl;
        std::cout << "--------- Map1 ----------" << std::endl;
        printSizeMap(mp_std);
        std::cout << "--------- Map2 ----------" << std::endl;
        printSizeMap(mp_std2);

        start2 = std::clock();
        mp_std.swap(mp_std2);
        end2 = std::clock();

        std::cout << "---- STD After swap ----" << std::endl;
        std::cout << "--------- Map1 ---------" << std::endl;
        printSizeMap(mp_std);
        std::cout << "--------- Map2 ---------" << std::endl;
        printSizeMap(mp_std2);

        std::string toPrint;
        toPrint = (mp_ft[0] == mp_std[0] && mp_ft2[0] == mp_std2[0]) ? "Swap : ✅" : "Swap : ❌";
        std::cout << toPrint << std::endl;

        double time = (end2 - start2) == 0 ? 1 : (end2 - start2);
        toPrint = ((end1 - start1) > (time * 20)) ? FRED("Diff Time KO") : FGRN("Diff Time OK");
        std::cout << toPrint << std::endl << std::endl;
    }
    {
        std::cout << "######### Operators #########" << std::endl;

        _ft<T1, T2> mp1;
        _ft<T1, T2> mp2;
        bool ret_ft[6];
        bool ret_std[6];

        mp1['a'] = 2; mp1['b'] = 3; mp1['c'] = 4; mp1['d'] = 5;
        mp2['a'] = 2; mp2['b'] = 3; mp2['c'] = 4; mp2['d'] = 5;

        _std<T1, T2> smp1;
        _std<T1, T2> smp2;

        smp1['a'] = 2; smp1['b'] = 3; smp1['c'] = 4; smp1['d'] = 5;
        smp2['a'] = 2; smp2['b'] = 3; smp2['c'] = 4; smp2['d'] = 5;


        mp2['e'] = 6; mp2['f'] = 7; mp2['h'] = 8; mp2['h'] = 9;
        smp2['e'] = 6; smp2['f'] = 7; smp2['h'] = 8; smp2['h'] = 9;

        (++(++mp1.begin()))->second = 42;
        (++(++smp1.begin()))->second = 42;

        start1 = std::clock();
        ret_ft[0] = (mp1 == mp2);
        ret_ft[1] = (mp1 != mp2);
        ret_ft[2] = (mp1 < mp2);
        ret_ft[3] = (mp1 > mp2);
        ret_ft[4] = (mp1 <= mp2);
        ret_ft[5] = (mp1 >= mp2);
        end1 = std::clock();

        start2 = std::clock();
        ret_std[0] = (smp1 == smp2);
        ret_std[1] = (smp1 != smp2);
        ret_std[2] = (smp1 < smp2);
        ret_std[3] = (smp1 > smp2);
        ret_std[4] = (smp1 <= smp2);
        ret_std[5] = (smp1 >= smp2);
        end2 = std::clock();
        
        std::string toPrint;
        toPrint = (ret_ft[0] == ret_std[0]
                    && ret_ft[1] == ret_std[1]
                    && ret_ft[2] == ret_std[2]
                    && ret_ft[3] == ret_std[3]
                    && ret_ft[4] == ret_std[4]
                    && ret_ft[5] == ret_std[5]) ? "Relational operators : ✅" : "Relational operators : ❌";
        std::cout << toPrint << std::endl;

        double time = (end2 - start2) == 0 ? 1 : (end2 - start2);
        toPrint = ((end1 - start1) > (time * 20)) ? FRED("Diff Time KO") : FGRN("Diff Time OK");
        std::cout << toPrint << std::endl << std::endl;
    }
}
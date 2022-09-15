#include "../inc/tests_utils.hpp"

static double start1;
static double start2;
static double end1;
static double end2;

void tests_stack()
{
    {
        std::cout << "######### Constructors ###########" << std::endl;

        start1 = std::clock();
        _fstack<int> fstack;
        for (int i = 0; i < 100; i++)
            fstack.push(8);
        _fstack<int> fstack2(fstack);
        _fstack<int> fstack3 = fstack2;
        end1 = std::clock();

        start2 = std::clock();
        _sstack<int> sstack;
        for (int i = 0; i < 100; i++)
            sstack.push(8);
        _sstack<int> sstack2(sstack);
        _sstack<int> sstack3 = sstack2;
        end2 = std::clock();

        std::string toPrint;

        std::cout << "Default -> ";
        controlSize(fstack, sstack);
        std::cout << "Copy -> ";
        controlSize(fstack2, sstack2);
        std::cout << "Overload assignment -> ";
        controlSize(fstack3, sstack3);

        double time = (end2 - start2) == 0 ? 1 : (end2 - start2);
        toPrint = ((end1 - start1) > (time * 20)) ? FRED("Diff Time KO") : FGRN("Diff Time OK");
        std::cout << toPrint << std::endl << std::endl;
    }
    {
        std::cout << "########### Empty ############" << std::endl;

        bool ret[4];
        
        _fstack<int> fstack;
        _fstack<int> fstack2;
        fstack2.push(8);

        start1 = std::clock();
        ret[0] = fstack.empty();
        ret[1] = fstack2.empty();
        end1 = std::clock();

        _sstack<int> sstack;
        _sstack<int> sstack2;
        sstack2.push(8);

        start2 = std::clock();
        ret[2] = sstack.empty();
        ret[3] = sstack2.empty();
        end2 = std::clock();

        std::string toPrint;
        toPrint = ((ret[0] == ret[2]) && (ret[1] == ret[3])) ? "Empty : ✅" : "Empty : ❌";
        std::cout << toPrint << std::endl;

        double time = (end2 - start2) == 0 ? 1 : (end2 - start2);
        toPrint = ((end1 - start1) > (time * 20)) ? FRED("Diff Time KO") : FGRN("Diff Time OK");
        std::cout << toPrint << std::endl << std::endl;
    }
    {
        std::cout << "########### Push #############" << std::endl;

        _fstack<int> fstack;
        start1 = std::clock();
        for (int i = 0; i < 1000; i++)
            fstack.push(i);
        end1 = std::clock();

        _sstack<int> sstack;
        start2 = std::clock();
        for (int i = 0; i < 1000; i++)
            sstack.push(i);
        end2 = std::clock();

        std::string toPrint;

        std::cout << "Push -> ";
        controlSize(fstack, sstack);

        double time = (end2 - start2) == 0 ? 1 : (end2 - start2);
        toPrint = ((end1 - start1) > (time * 20)) ? FRED("Diff Time KO") : FGRN("Diff Time OK");
        std::cout << toPrint << std::endl << std::endl;

        std::cout << "########### Pop #############" << std::endl;

        start1 = std::clock();
        for (int i = 0; i < 500; i++)
            fstack.pop();
        end1 = std::clock();

        start2 = std::clock();
        for (int i = 0; i < 500; i++)
            sstack.pop();
        end2 = std::clock();

        std::cout << "Pop -> ";
        controlSize(fstack, sstack);

        time = (end2 - start2) == 0 ? 1 : (end2 - start2);
        toPrint = ((end1 - start1) > (time * 20)) ? FRED("Diff Time KO") : FGRN("Diff Time OK");
        std::cout << toPrint << std::endl << std::endl;
    }
    {
        std::cout << "########### Top #############" << std::endl;

        _fstack<int> fstack;
        for (int i = 0; i < 10; i++)
            fstack.push(i);
        start1 = std::clock();
        int ret_f = fstack.top();
        end1 = std::clock();

        _sstack<int> sstack;
        for (int i = 0; i < 10; i++)
            sstack.push(i);
        start2 = std::clock();
        int ret_s = fstack.top();
        end2 = std::clock();

        std::string toPrint;
        toPrint = (ret_f == ret_s) ? "Top : ✅" : "Top : ❌";
        std::cout << toPrint << std::endl;

        double time = (end2 - start2) == 0 ? 1 : (end2 - start2);
        toPrint = ((end1 - start1) > (time * 20)) ? FRED("Diff Time KO") : FGRN("Diff Time OK");
        std::cout << toPrint << std::endl << std::endl;
    }
    {
        std::cout << "###### Relational Operators ######" << std::endl;

        bool ret_ft[6];
        bool ret_std[6];

        _fstack<int> fstack;
        for (int i = 0; i < 10; i++)
            fstack.push(i);
        fstack.push(14);
        fstack.push(-4);

        _fstack<int> fstack2;
        for (int i = 0; i < 10; i++)
            fstack2.push(i);
        fstack2.push(13);
        fstack2.push(-4);

        _sstack<int> sstack;
        for (int i = 0; i < 10; i++)
            sstack.push(i);
        sstack.push(14);
        sstack.push(-4);

        _sstack<int> sstack2;
        for (int i = 0; i < 10; i++)
            sstack2.push(i);
        sstack2.push(13);
        sstack2.push(-4);

        start1 = std::clock();
        ret_ft[0] = (fstack == fstack2);
        ret_ft[1] = (fstack != fstack2);
        ret_ft[2] = (fstack < fstack2);
        ret_ft[3] = (fstack > fstack2);
        ret_ft[4] = (fstack <= fstack2);
        ret_ft[5] = (fstack >= fstack2);
        end1 = std::clock();

        start2 = std::clock();
        ret_std[0] = (sstack == sstack2);
        ret_std[1] = (sstack != sstack2);
        ret_std[2] = (sstack < sstack2);
        ret_std[3] = (sstack > sstack2);
        ret_std[4] = (sstack <= sstack2);
        ret_std[5] = (sstack >= sstack2);
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
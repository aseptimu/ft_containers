#include "vector.hpp"
// #include "tree.hpp"
#include <map>

using namespace std;


int main(void)
{
    {
        ft::vector<int> i;
        std::map<int, std::string> ma;
        std::pair<int, std::string> p(1, "Hello");
        ma.insert(p);
        std::map<int, std::string>::iterator it = ma.begin();
        std::cout << (*it).second << std::endl;
    }

    {
        cout<<endl;
        ft::Tree<int>::_node_allocator all;
        ft::TreeIterator<int>::Node_ptr iz;
        iz = all.allocate(1);
        ft::TreeIterator<int> ii(iz);
        iz->_value = 10;
        int i = *ii;
        std::cout << i << endl;

        cout << endl;
        ft::TreeIterator<int> zz(iz);
        int *l = zz.operator->();
    }
    // {
    //     std::map<int, string> i;
    //     i.emplace(30, "hello");
    //     i.emplace(15, "world");
    //     i.emplace(70, "world");
    //     i.emplace(10, "world");
    //     i.emplace(20, "world");
    //     i.emplace(60, "world");
    //     i.emplace(85, "world");
    //     i.emplace(5, "world");
    //     i.emplace(50, "world");
    //     i.emplace(65, "world");
    //     i.emplace(80, "world");
    //     i.emplace(90, "world");
    //     std::map<int, string>::iterator it;
    //     it = i.begin();
    //     std::cout << (*it).first << endl;
    //     it++;
    //     std::cout << (*it).first << endl;
    //     it++;
    //     it++;
    //     it++;
    //     it++;
    //     it++;
    //     it++;
    //     it++;
    //     it++;
    //     it++;
    //     it++;
    //     it++;
    //     it++;
    //     it++;
    //     it++;
    //     it++;
    //     it++;
    //     std::cout << (*it).first << endl;
    //     it--;
    //     std::cout << (*it).first << endl;

    // }

}
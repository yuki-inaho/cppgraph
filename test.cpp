#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "cppgraph.h"

class ToyClass
{
public:
    char m_id;
    ToyClass(char m_id) : m_id(m_id){};
    friend bool operator==(const ToyClass &obj1, const ToyClass &obj2)
    {
        return obj1.m_id == obj2.m_id;
    };
    friend std::ostream &operator<<(std::ostream &os, const ToyClass &it)
    {
        return os << it.m_id;
    };
};

int main(int argc, char *argv[])
{
    /// example 1
    printf("<<< example ND:char, LD: int >>> \n");

    typedef Graph<char, int> GraphCharInt;
    typedef Node<char, int> NodeCharInt;
    typedef Link<char, int> LinkCharInt;
    GraphCharInt g;

    auto dump = [&]()
    {
        g.forEachNode([&](NodeCharInt *n)
                      {
                          printf("Node '%c'\n", n->data);
                          n->forEachOutgoingLink([&](LinkCharInt *L)
                                                 {
                                                     printf(" %i → '%c'\n", L->data, L->to->data);
                                                     return true;
                                                 });
                          n->forEachIncomingLink([&](LinkCharInt *L)
                                                 {
                                                     printf(" %i ← '%c'\n", L->data, L->from->data);
                                                     return true;
                                                 });
                          return true;
                      });
    };

    auto a = g.addNode('a'), b = g.addNode('b'), c = g.addNode('c'), x = g.addNode('x');
    g.addLink(1, a, b);
    g.addLink(2, b, c);
    g.addLink(3, c, a);
    g.addLink(4, a, x);
    g.addLink(5, x, a);
    g.addLink(6, b, x);
    g.addLink(7, x, b);
    g.addLink(8, c, x);
    g.addLink(9, x, c);

    printf("Before ---------\n");
    dump();
    delete x;
    printf("After ----------\n");
    dump();


    printf("<<< example 2. ND:ToyClass, LD: int >>> \n");

    typedef Graph<ToyClass, int> GraphToyInt;
    typedef Node<ToyClass, int> NodeToyInt;
    typedef Link<ToyClass, int> LinkToyInt;
    std::vector<ToyClass *> toy_vector;
    GraphToyInt g2;

    toy_vector.push_back(new ToyClass('a'));
    toy_vector.push_back(new ToyClass('b'));
    toy_vector.push_back(new ToyClass('c'));
    toy_vector.push_back(new ToyClass('x'));

    auto dump2 = [&]()
    {
        g2.forEachNode([&](NodeToyInt *n)
                       {
                           printf("Node '%c'\n", n->data);
                           n->forEachOutgoingLink([&](LinkToyInt *L)
                                                  {
                                                      printf(" %i → '%c'\n", L->data, L->to->data);
                                                      return true;
                                                  });
                           n->forEachIncomingLink([&](LinkToyInt *L)
                                                  {
                                                      printf(" %i ← '%c'\n", L->data, L->from->data);
                                                      return true;
                                                  });
                           return true;
                       });
    };

    auto a2 = g2.addNode(*toy_vector[0]);
    auto b2 = g2.addNode(*toy_vector[1]);
    auto c2 = g2.addNode(*toy_vector[2]);
    auto x2 = g2.addNode(*toy_vector[3]);

    g2.addLink(1, a2, b2);
    g2.addLink(2, b2, c2);
    g2.addLink(3, c2, a2);
    g2.addLink(4, a2, x2);
    g2.addLink(5, x2, a2);
    g2.addLink(6, b2, x2);
    g2.addLink(7, x2, b2);
    g2.addLink(8, c2, x2);
    g2.addLink(9, x2, c2);

    printf("Before ---------\n");
    dump2();
    /*
    toy_vector.erase(
        std::remove_if(
            toy_vector.begin(),
            toy_vector.end(),
            [&](auto const toy_obj_ptr)
            { return *toy_obj_ptr == *toy_vector[3]; }),
        toy_vector.end());
    toy_vector.shrink_to_fit();    

    std::cout << x2->data.m_id << std::endl;  // -> x
    //std::cout << toy_vector[3]->m_id << std::endl;  // cause Segmentation fault
    */    
    delete x2;
    printf("After ----------\n");
    dump2();


    /*
    std::cout << *toy_vector[3] << std::endl;
        -> x

    g2.addLink(4, a2, x2);
        ->  terminate called after throwing an instance of 'std::runtime_error'
            what():  Cannot link nodes from different graphs
            Aborted (core dumped)
    */

    return 0;
}

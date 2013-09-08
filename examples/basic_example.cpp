#include <iostream>
#include "Person.hpp"
#include "basic_example.hpp"

struct Assembly
{
  typedef Person Business;
  typedef IA1<IB52<Assembly> > Whole;
  // typedef IA2<Assembly> Whole;
};

int main()
{
  typedef Assembly::Whole::Business AspectizedPerson;
  AspectizedPerson p("Toto");

  //  std::cout << static_cast<typename GetAspect<Assembly::Whole, IB52>::Type>(p) << std::endl;
  std::cout << p << std::endl;

  //  p.functionB();
}

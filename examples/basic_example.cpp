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

  auto *a = static_cast<typename GetAspect<Assembly::Whole, IB52>::Type::Business*>(&p);
  a->function();
  static_cast<typename GetAspect<Assembly::Whole, IA1>::Type::Business*>(a)->function();

  std::cout << "---------------" << std::endl;

  //  static_cast<typename GetUpperAspect<>::Type::Business*>
  std::cout << p << std::endl;

  //  p.functionB();
}

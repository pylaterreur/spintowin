#include <typeinfo>
#include <iostream>
#include "Assembly.hpp"

#include "../examples/Utility.hpp"

template <typename Super>
struct B52 : Super
{
  struct Business : Super::Business
  {
    template <typename... T>
    Business(T&&... t) : Super::Business(t...)
    {
      std::cout << "B52" << std::endl;
    }
  };
};

template <typename Super>
struct A1 : Super
{
  struct Business : Super::Business
  {
    template <typename... T>
    Business(T&&... t) : Super::Business(t...)
    {
      std::cout << "A1" << std::endl;
    }
  };
};

template <typename Super>
struct A2 : Super
{
  struct Business : Super::Business
  {
    template <typename... T>
    Business(T&&... t) : Super::Business(t...)
    {
      std::cout << "A2" << std::endl;
    }
  };
};

struct Foo
{
  Foo(const std::string &str)
  {
    std::cout << str << std::endl;
  }
};

int main()
{
  Assembly<Foo, A1, B52>::Whole::Business f("abc");
  std::cout << typeid(decltype(f)).name() << std::endl;

  // compiles ;)
  GetAspect<decltype(f)::BusinessToWhole, A1>::Type::Business p("hihi");
  std::cout << typeid(decltype(p)).name() << std::endl;

  // does not compile! ;)
  // GetAspect<decltype(p)::BusinessToWhole, A2>::Type::Business p2("hihi");
  //  std::cout << typeid(decltype(p2)).name() << std::endl;

  //  std::cout << std::boolalpha << AspectIsLast<Assembly<Foo>::Whole::Business>::result << std::endl;
}

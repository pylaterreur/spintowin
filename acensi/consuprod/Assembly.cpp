#include <iostream>
#include "Assembly.hpp"

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
}

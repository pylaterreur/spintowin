#include <typeinfo>
#include <iostream>
#include <type_traits>

#include "Assembly.hpp"

#include "Utility.hpp"

struct Aspect
{};

struct AspectA : Aspect
{};

struct AspectB : Aspect
{};

template <typename Super>
struct B52 : Super
{
  typedef AspectB Implem;

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
  typedef AspectA Implem;
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
  typedef AspectA Implem;
  struct Business : Super::Business
  {
    template <typename... T>
    Business(T&&... t) : Super::Business(t...)
    {
      std::cout << "A2" << std::endl;
    }
  };
};

template <typename Super>
struct A3 : Super
{
  typedef AspectA Implem;
  struct Business : Super::Business
  {
    template <typename... T>
    Business(T&&... t) : Super::Business(t...)
    {
      std::cout << "A3" << std::endl;
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
  // for Assembly
  using namespace Aop;
  // for more "advanced" Aop utilities
  using namespace Aop::Implem;

  {
    // Let's unit-test the library at compile-time!
    typedef Assembly<Foo, A1>::Whole Toto1;
    typedef Assembly<Foo, A1, A2>::Whole Toto2;
    typedef Assembly<Foo, A1, A1>::Whole Toto3;

    static_assert(IsSameChain<Toto1, Toto2>::value == false, "Assembly<Foo, A1>::Whole and Assembly<Foo, A1, A2>::Whole aren't supposed to be same chain");
    static_assert(IsSameChain<Toto2, Toto3>::value == false, "Assembly<Foo, A1, A2>::Whole and Assembly<Foo, A1, A1>::Whole aren't supposed to be same chain");
    static_assert(IsSameChain<PrevChain<Toto2>::Type, Toto2>::value == true, "PrevChain<Assembly<Foo, A1, A2>::Whole>::Type and Assembly<Foo, A1, A2>::Whole are supposed to be same chain");
    static_assert(IsSameChain<NextChain<Toto1>::Type, Toto1>::value == true, "NextChain<Assembly<Foo, A1>::Whole>::Type and Assembly<Foo, A1>::Whole are supposed to be same chain");
    static_assert(IsSameChain<PrevChain<NextChain<Toto2>::Type>::Type, Toto2>::value == true, "PrevChain<NextChain<Assembly<Foo, A1, A2>::Whole>::Type>::Type and Assembly<Foo, A1, A2>::Whole are supposed to be same chain");
    static_assert(IsSameChain<NextChain<Toto2>::Type, Toto1>::value == true, "NextChain<Assembly<Foo, A1, A2>::Whole>::Type and Assembly<Foo, A1>::Whole are supposed to be same chain");
    {
      typedef Get<Toto2::Business::BusinessToWhole, A1>::Type GetTest;
      static_assert(IsSameChain<GetTest, Toto1>::value == true, "Get<Assembly<Foo, A1, A2>::Whole::Business::BusinessToWhole, A1>::Type and Assembly<Foo, A1>::Whole are supposed to be same chain");
    }
  }

  {
    // Runtime test
    typedef Assembly<Foo, A1, A3, B52>::Whole Toto;
    // here we have an f variable of type Foo, aspectized by A1, the A1<Foo> aspectized by A3, aspectized by B52
    Toto::Business f("abc");
    std::cout << typeid(decltype(f)).name() << std::endl;

    // here, p is using the layers of Toto starting from the A3 layer, aka A3<A1<Foo> >
    Get<decltype(f)::BusinessToWhole, A3>::Type::Business p("hihi");
    std::cout << typeid(decltype(p)).name() << std::endl;
  }
}

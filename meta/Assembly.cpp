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
  using namespace Aop;
  using namespace Aop::Implem;

  typedef Assembly<Foo, A1, A3, B52>::Whole Toto;
  Toto::Business f("abc");
  std::cout << typeid(decltype(f)).name() << std::endl;

  // compiles ;)
  Get<decltype(f)::BusinessToWhole, A1>::Type::Business p("hihi");
  std::cout << typeid(decltype(p)).name() << std::endl;

  // does not compile! ;)
  // Get<decltype(p)::BusinessToWhole, A2>::Type::Business p2("hihi");
  //  std::cout << typeid(decltype(p2)).name() << std::endl;

  static_assert(std::is_same<Toto, PrevChain<Toto>::Type>::value, "lol");

  static_assert(std::is_same<Toto, PrevChain<NextChain<Toto>::Type>::Type>::value, "lol");

  //  static_assert(std::is_same<Toto, NextChain<PrevChain<Toto>::Type>::Type>::value, "lol");
  
  std::cout << "--------------------------" << std::endl;

  static_assert(std::is_same<
  		  NextChain<NextChain<Toto>::Type>::Type,
		  NextChain<
  		  PrevChain<
  		  NextChain<NextChain<Toto>::Type>::Type
  		    >::Type
		    >::Type
  		  >::value, "lol");

  //  std::cout << std::boolalpha << AspectIsLast<Assembly<Foo>::Whole::Business>::result << std::endl;

  {
    typedef Assembly<Foo, A1>::Whole Toto1;
    typedef Assembly<Foo, A1, A2>::Whole Toto2;
    typedef Assembly<Foo, A1, A1>::Whole Toto3;

    static_assert(IsSameChain<Toto1, Toto2>::value == false, "Assembly<Foo, A1>::Whole and Assembly<Foo, A1, A2>::Whole aren't supposed to be same chain");
    static_assert(IsSameChain<Toto2, Toto3>::value == false, "Assembly<Foo, A1, A2>::Whole and Assembly<Foo, A1, A1>::Whole aren't supposed to be same chain");
    static_assert(IsSameChain<PrevChain<Toto2>::Type, Toto2>::value == true, "PrevChain<Assembly<Foo, A1, A2>::Whole>::Type and Assembly<Foo, A1, A2>::Whole are supposed to be same chain");
    static_assert(IsSameChain<NextChain<Toto1>::Type, Toto1>::value == true, "NextChain<Assembly<Foo, A1>::Whole>::Type and Assembly<Foo, A1>::Whole are supposed to be same chain");
    static_assert(IsSameChain<NextChain<Toto2>::Type, Toto1>::value == true, "NextChain<Assembly<Foo, A1, A2>::Whole>::Type and Assembly<Foo, A1>::Whole are supposed to be same chain");
  }

}

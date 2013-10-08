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
  typedef Assembly<Foo, A1, A3, B52>::Whole Toto;
  Toto::Business f("abc");
  std::cout << typeid(decltype(f)).name() << std::endl;

  // compiles ;)
  GetAspect<decltype(f)::BusinessToWhole, A1>::Type::Business p("hihi");
  std::cout << typeid(decltype(p)).name() << std::endl;

  // does not compile! ;)
  // GetAspect<decltype(p)::BusinessToWhole, A2>::Type::Business p2("hihi");
  //  std::cout << typeid(decltype(p2)).name() << std::endl;

  static_assert(std::is_same<Toto, GetPrevChain<Toto>::Type>::value, "lol");

  static_assert(std::is_same<Toto, GetPrevChain<GetNextChain<Toto>::Type>::Type>::value, "lol");

  //  static_assert(std::is_same<Toto, GetNextChain<GetPrevChain<Toto>::Type>::Type>::value, "lol");
  
  std::cout << "--------------------------" << std::endl;

  static_assert(std::is_same<
  		  GetNextChain<GetNextChain<Toto>::Type>::Type,
		  GetNextChain<
  		  GetPrevChain<
  		  GetNextChain<GetNextChain<Toto>::Type>::Type
  		    >::Type
		    >::Type
  		  >::value, "lol");

  //  std::cout << std::boolalpha << AspectIsLast<Assembly<Foo>::Whole::Business>::result << std::endl;
}

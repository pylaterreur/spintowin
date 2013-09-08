
#include <typeinfo>
#include <iostream>

struct Foo
{
  int f(char)
  {
    return (42);
  }

  int f(double)
  {
    return (42);
  }
};

template <typename Class>
struct getUnderlyingFunctionType
{
  template <typename Ret, typename... Args>
  static typename std::add_pointer<Ret(Args...)>::type caca(Ret (Class::*p)(Args...));
};

template <typename Implem>
struct Concept : Implem
{
  using Implem::f;
  static const char tab[-(int)
			!std::is_same<
			  typename std::remove_pointer<decltype(getUnderlyingFunctionType<Implem>::caca(&Implem::f))>::type,
			  // BELOW IS THE SIGNATURE WE WANT TO FIND FOR f!
			  int(char)
			  >::value
			];
  enum { useless };
};

namespace {
  struct Useless
  {
    // Foo doit respecter les regles definies dans Concept
    enum { useless = Concept<Foo>::useless};
  };
}

int main()
{
}

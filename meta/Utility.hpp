#ifndef UTILITY_HPP_
# define UTILITY_HPP_

# include "Assembly.hpp"

namespace Aop
{
namespace Implem
{
template <typename Chain, template <typename, typename...> class Aspect>
struct Get;

template <template <typename, typename...> class FirstAspect, template <typename, typename...> class Aspect, typename First, typename ...Args>
struct Get<FirstAspect<First, Args...>, Aspect>
{
  typedef typename Get<First, Aspect>::Type Type;
};

template <template <typename, typename...> class Aspect, typename First, typename... Args>
struct Get<Aspect<First, Args...>, Aspect>
{
  typedef Aspect<First> Type;
};

template <typename Chain>
struct NextChain;

template <template <typename, typename...> class LastLayer, typename ...Args, typename Implem, template <typename, typename...> class... Layers>
struct NextChain<LastLayer<Assembly<Implem, Layers...>, Args... > >
{
  typedef LastLayer<Assembly<Implem, Layers...>, Args... > Type;
};

template <template <typename, typename...> class Aspect, typename First, typename... Args>
struct NextChain<Aspect<First, Args...> >
{
  typedef First Type;
};

template <typename Chain>
struct PrevChain
{
private:
  template <typename T, bool notChain = !std::is_same<Chain, T>::value, bool Dummy = false>
  struct Helper;

  template <bool Dummy>
  struct Helper<Chain, false, Dummy>
  {
    typedef Chain Type;
  };

  template <template <typename, typename...> class Prev, typename ...Args, bool Dummy>
  struct Helper<Prev<Chain, Args...>, true, Dummy>
  {
    typedef Prev<Chain, Args...> Type;
  };

  template <template <typename, typename...> class Prev, typename Next, typename ...Args, bool Dummy>
  struct Helper<Prev<Next, Args...>, true, Dummy>
  {
    typedef typename Helper<Next>::Type Type;
  };

public:
  typedef typename Helper<typename Chain::Whole>::Type Type;
};

template <typename Aspect>
struct AspectIsLast
{
  static const bool result = std::is_same<typename Implem::NextChain<Aspect>::Type, Aspect>::value;
};

template <typename Chain1, typename Chain2>
struct IsSameChain
{
  static const bool value = false;
};

template <template <typename, typename...> class FirstAspect, typename First1, typename First2, typename ...Args1, typename ...Args2>
struct IsSameChain<FirstAspect<First1, Args1...>, FirstAspect<First2, Args2...> >
{
private:
  static const bool first_is_last = AspectIsLast<FirstAspect<First1, Args1...> >::result;
  static const bool second_is_last = AspectIsLast<FirstAspect<First2, Args2...> >::result;

public:
  static const bool value = (first_is_last && second_is_last) ?
    true :
    (first_is_last == second_is_last ? IsSameChain<First1, First2>::value : false);
};

}

}

#endif	// !UTILITY_HPP_

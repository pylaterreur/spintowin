#ifndef ASSEMBLY_HPP_
# define ASSEMBLY_HPP_

namespace Aop
{
template <typename Implem, template <typename, typename...> class... Layers>
struct Assembly
{
private:
  template <typename HSubWhole, template <typename, typename...> class... HLayers>
  struct AssemblyHelper;

  template <typename HSubWhole, template <typename, typename...> class HFirstLayer, template <typename, typename...> class... HLayers>
  struct AssemblyHelper<HSubWhole, HFirstLayer, HLayers...>
  {
    typedef typename AssemblyHelper<HFirstLayer<HSubWhole>, HLayers...>::Whole Whole;
  };

  template <typename HSubWhole>
  struct AssemblyHelper<HSubWhole>
  {
    typedef HSubWhole Whole;
  };


public:
  struct Business;
  // typedef Implem Business;
  typedef typename AssemblyHelper<Assembly, Layers...>::Whole Whole;
  struct Business : Implem
  {
    using Implem::Implem;

    typedef Whole BusinessToWhole;
  };
};
}

#endif

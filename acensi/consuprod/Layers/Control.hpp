#ifndef LAYERS_CONTROL_HPP_
# define LAYERS_CONTROL_HPP_

namespace Layers
{
template <typename Super>
struct Control : Super
{
  struct Business : Super::Business
  {
    template <typename... T>
    Business(T&&... t) : Super::Business(t...)
    {
      for (auto &&p : reader_end_)
	p = 0;
      for (auto && p : Super::Business::buffer_)
	{
	  //	  p = new std::string("lol");
	}
    }

  protected:
    int reader_end_[Super::Business::Size];
    unsigned min_r_;
  };
};
}

#endif

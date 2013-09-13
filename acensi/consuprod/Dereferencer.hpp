#ifndef DEREFERENCER_HPP_
# define DEREFERENCER_HPP_

template <typename Super>
struct Dereferencer : Super
{
public:
  struct Business : Super::Business
  {
    template <typename... T>
    Business(T&&... t) : Super::Business(t...)
    {}

    operator typename Super::Business::value_type::element_type() const;
  };
};

#endif

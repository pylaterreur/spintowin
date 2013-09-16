#ifndef LAYERS_CONSUMER_HPP_
# define LAYERS_CONSUMER_HPP_

namespace Layers
{
template <typename Super>
struct Consumer : Super
{
private:
  struct iterator : std::iterator<std::input_iterator_tag, typename Super::Business::value_type>, iterator_base
  {
    typedef typename Super::Business::value_type value_type;
    typedef typename Super::Whole::Business QueueType;

  private:
    template <typename T>
    struct Container
    {
      typedef T value_type;
    };

    // template <template <typename...> class C, typename T, typename ...Others>
    // struct Container <C<T, Others...> >
    // {
    //   typedef T value_type;
    // };

  public:
    typename Container<typename Super::Business::value_type>::value_type operator*() const
    {
      return (q_->buffer_[r_]);
    }

    iterator() : q_(0), ref_counter_(new unsigned (1)), r_(0)
    {}

    iterator(const iterator &copy) : q_(copy.q_), ref_counter_(copy.ref_counter_), r_(copy.r_)
    {
      ++*ref_counter_;
    }

    iterator(QueueType &q) : q_(&q), ref_counter_(new unsigned (1))
    {
      // ATOMIC PLEASE
      r_ = q_->r_++;
    }

    ~iterator()
    {
      --*ref_counter_;
      // ATOMIC PLEASE
      if (*ref_counter_ == 0)
	{
	  q_->reader_end_[r_] = 1;
	  if (r_ == q_->min_r_)
	    {
	      while (q_->reader_end_[q_->r_])
		{
		  q_->reader_end_[q_->r_] = 0;
		  ++q_->min_r_;
		  if (q_->min_r_ >= sizeof(q_->reader_end_) / sizeof(*q_->reader_end_))
		    q_->min_r_ = 0;
		}
	    }
	  delete ref_counter_;
	}
    }

    // we aint caring about exception safety and Herb Sutter stuff
    // http://stackoverflow.com/questions/7177884/can-i-use-placement-newthis-in-operator
    iterator &operator=(iterator &&copy)
    {
      if (this != &copy)
	{
	  QueueType& q = *q_;
	  this->~iterator();
	  new(this) iterator(q);
	}
      return (*this);
    }

    iterator operator++(int) = delete;

    iterator operator++()
    {
      QueueType& q = *q_;
      this->~iterator();
      new (this) iterator(q);
      return (*this);
    }

    QueueType *q_;
    unsigned r_;
    // make it atomic?
    unsigned *ref_counter_;
  };

public:
  struct Business : Super::Business
  {
    template <typename... T>
    Business(T&&... t) : Super::Business(t...)
    {}

    iterator consume_begin()
    {
      return (iterator(*static_cast<typename Super::Whole::Business*>(this)));
    }

    iterator end()
    {
      return (iterator());
    }

    friend iterator;
  };

};
}

#endif

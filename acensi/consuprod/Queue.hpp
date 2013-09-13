#ifndef QUEUE_HPP_
# define QUEUE_HPP_

template <typename T>
struct Queue
{
  typedef std::shared_ptr<T> value_type;

protected:
  void insert(value_type data)
  {
    buffer_[r_ & (Size - 1)] = data;
    i_ = (i_ + 1) & (Size - 1);
  }

  value_type pop()
  {
    value_type ret;

    ret = buffer_[i_];
    //    buffer_[i_] = value_type();
    r_ = (r_ + 1) & (Size - 1);
    return (ret);
  }

protected:
  static const unsigned Size = 1 << 3;
  unsigned	i_, r_;
  value_type	buffer_[Size];
};

#endif

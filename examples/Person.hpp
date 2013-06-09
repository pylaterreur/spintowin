#ifndef PERSON_HPP_
# define PERSON_HPP_

# include <string>
# include <iosfwd>

class Person
{
public:
  Person(const std::string &name);
  const std::string &name() const;

private:
  std::string name_;
  friend std::ostream &operator<<(std::ostream &output, const Person &person);
};

#endif	// !PERSON_HPP_

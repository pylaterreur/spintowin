
#include <iostream>

#include "Person.hpp"

Person::Person(const std::string &name) : name_(name)
{}

std::ostream &operator<<(std::ostream &output, const Person &person)
{
  output << "I am a Person, and my name is \"" << person.name_ << '"';
  return (output);
}

const std::string &Person::name() const
{
  return (name_);
}

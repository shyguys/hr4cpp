#ifndef HR4CPP_LIB_HPP
#define HR4CPP_LIB_HPP

#include <string>

class LengthException : public std::exception {
public:
  int more_required;

  LengthException(int more_required);

  std::string what();
};

std::string str_strip(const std::string str);

void print_untitled(int length, std::string outer, char inner);

void print_titled(int length, std::string outer, char inner, std::string title);

void print_as_paragraph(int length, std::string outer, char inner,
                        std::string title);

#endif // HR4CPP_LIB_HPP

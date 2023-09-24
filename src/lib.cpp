#include "lib.hpp"

#include <exception>
#include <iostream>
#include <string>

LengthException::LengthException(int more_required) {
  this->more_required = more_required;
}

std::string LengthException::what() {
  return std::string("length insufficient, ")
      .append(std::to_string(more_required))
      .append(" more required");
}

// Strips a string of leading and trailing whitespaces.
// Parameters:
// - `std::string str`: the string to strip.
// Returns:
// - Stripped string.
std::string str_strip(const std::string str) {
  int begin = 0, end = str.length() - 1;
  if (end < 0)
    return std::string("");
  for (int i = begin; i <= end; i++) {
    if (!std::isspace((unsigned)str.at(i))) {
      break;
    }
    begin++;
  }
  for (int i = end; i > begin; i--) {
    if (!std::isspace((unsigned)str.at(i))) {
      break;
    }
    end--;
  }
  return str.substr(begin, end - begin + 1);
}

void print_untitled(int length, std::string outer, char inner) {
  int spare_length = length - outer.length() * 2 - 2;
  if (spare_length < 1)
    throw LengthException(1 - spare_length);
  std::cout << outer << ' ' << std::string(spare_length, inner) << ' ' << outer
            << '\n';
}

void print_titled(int length, std::string outer, char inner,
                  std::string title) {
  int spare_length = length - outer.length() * 2 - title.length() - 4;
  if (spare_length < 2)
    throw LengthException(2 - spare_length);
  int right_spare_length = spare_length / 2;
  int left_spare_length = spare_length - right_spare_length;
  std::cout << outer << ' ' << std::string(left_spare_length, inner) << ' '
            << title << ' ' << std::string(right_spare_length, inner) << ' '
            << outer << '\n';
}

void print_as_paragraph(int length, std::string outer, char inner,
                        std::string title) {
  std::string begin = "BEGIN", end = "END";
  if (title.length() > 0) {
    begin.append(" ").append(title);
    end.append(" ").append(title);
  }
  print_titled(length, outer, inner, begin);
  print_titled(length, outer, inner, end);
}

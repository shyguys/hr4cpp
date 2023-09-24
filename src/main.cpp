#include <unistd.h>

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "lib.hpp"

const std::string kProg = "hr4cpp";
const std::string kUsage =
    std::string("usage: ") + kProg +
    std::string("[-h] [-p] [-i STR] [-l INT] [-o STR] [title]");
const std::string kHelp = kUsage + std::string("\
                \n\
                positional arguments:\n\
                  title               title to insert in center\n\
                \n\
                options:\n\
                  -h, --help          show this help message and exit\n\
                  -p, --as-paragraph  print two horizontal rules, BEGIN and \
                END\n\
                \n\
                style proprties:\n\
                  -i, --inner STR     inner character (default: -)\n\
                  -l, --length INT    total character length (default: 80)\n\
                  -o, --outer STR     outer character(s) (default: #)");

int main(int argc, char *argv[]) {
  int opt;
  bool as_paragraph = false;
  char inner = '-';
  int length = 80;
  std::string outer = "//";

  while ((opt = getopt(argc, argv, "hpi:l:o:")) != -1) {
    switch (opt) {
    case 'h':
      std::cout << kHelp << '\n';
      return 0;
    case 'p':
      as_paragraph = true;
      break;
    case 'i':
      inner = std::string(optarg).at(0);
      break;
    case 'l':
      try {
        length = std::stoi(optarg);
        if (length < 0)
          throw std::invalid_argument("length must be greater than 0");
      } catch (const std::exception &e) {
        std::cerr << kProg << ": invalid int value '" << optarg << "' -- l\n"
                  << kUsage << '\n';
        return 1;
      }
      break;
    case 'o':
      outer = str_strip(std::string(optarg));
      break;
    case ':':
      std::cerr << kUsage << '\n';
      return 1;
    case '?':
      std::cerr << kUsage << '\n';
      return 1;
    }
  }
  std::string title = std::string("");
  if (argc > optind)
    title = argv[optind];

  try {
    if (as_paragraph) {
      print_as_paragraph(length, outer, inner, title);
    } else if (title.length() != 0) {
      print_titled(length, outer, inner, title);
    } else {
      print_untitled(length, outer, inner);
    }
  } catch (LengthException &e) {
    std::cerr << "[ERROR] " << e.what() << '\n';
    return 1;
  }

  return 0;
}

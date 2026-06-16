#include "Parameters.h"
#include <iostream>

int main(int argc, char **argv) {
  std::cout << "wersja lib: " << Parameters::getVersion() << "\n";

  if (Parameters::readParameters(argc - 1, argv + 1) != 0) {
    std::cerr << "blad parsowania argumentow \n";
    return 1;
  }

  Parameters::printParameters();

  return 0;
}
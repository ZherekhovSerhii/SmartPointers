#include <conio.h>
#include <iostream>

#include "unique_ptr.hpp"

int main(int argc, char *argv[]) {
  int *ptr = new int[5]{2, 2, 2, 2, 2};

  int *ptr1 = new int[1];

  {
    unique_ptr<int> raii_1{ptr};

    unique_ptr<int> raii_2{std::move(raii_1)};

    unique_ptr<int> raii_3{ptr1};

    raii_1 = std::move(raii_3);

    raii_2 = std::move(raii_3);
  }
  
  return 0;
}
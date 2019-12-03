#include <iostream>

#include "shared_ptr.hpp"

int main(int argc, char *argv[]) {
  int *ptr = new int[5]{2, 2, 2, 2, 2};

  int *ptr1 = new int[1];

  {
    shared_ptr<int> raii_1{ptr};

    shared_ptr<int> raii_2{raii_1};

    shared_ptr<int> raii_3{nullptr};

    raii_3 = raii_2;

    shared_ptr<int> raii_4{ptr1};

    shared_ptr<int> raii_5{std::move(raii_1)};

    shared_ptr<int> raii_6 = std::move(raii_2);
  }
  
  return 0;
}
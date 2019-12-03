#ifndef SHARED_PTR
#define SHARED_PTR

template <typename T> class shared_ptr {
public:
  shared_ptr(T *ptr);
  ~shared_ptr();

  shared_ptr(const shared_ptr<T> &raii);
  shared_ptr &operator=(const shared_ptr<T> &raii);

  shared_ptr(shared_ptr<T> &&raii) noexcept;
  shared_ptr &operator=(shared_ptr<T> &&raii) noexcept;

  bool isUnique();

  size_t Count();

private:
  T *storage;
  size_t *counter;
};

template <typename T>
shared_ptr<T>::shared_ptr(T *ptr = nullptr) : storage(ptr) {
  std::cout << "Constructed" << std::endl;
  counter = new size_t(1);
}

template <typename T> shared_ptr<T>::shared_ptr(const shared_ptr<T> &raii) {
  std::cout << "Constructed copy" << std::endl;

  if (raii.storage != nullptr) {
    counter = raii.counter;
    storage = raii.storage;
    ++(*counter);
  }
};

template <typename T>
shared_ptr<T> &shared_ptr<T>::operator=(const shared_ptr<T> &raii) {
  if (this != &raii) {
    if (counter == raii.counter) {
      counter = raii.counter;
      storage = raii.storage;
      ++(*counter);
    } else {
      --(*counter);
      counter = raii.counter;
      storage = raii.storage;
      ++(*counter);
    }
  }
  return *this;
};

template <typename T> shared_ptr<T>::shared_ptr(shared_ptr<T> &&raii) noexcept {
  std::cout << "Constructed move" << std::endl;

  if (raii.storage != nullptr) {
    storage = std::move(raii.storage);
    raii.storage = nullptr;
    counter = raii.counter;
  }
}

template <typename T>
shared_ptr<T> &shared_ptr<T>::operator=(shared_ptr<T> &&raii) noexcept {
  if (this != &raii) {
    if (((*counter) - 1) == 0) {
      std::cout << "Removed ptr" << std::endl;
      *counter = 0;
      if (storage != nullptr)
        delete storage;
    } else {
      --(*counter);
      counter = raii.counter;
    }

    storage = std::move(raii.storage);
    raii.storage = nullptr;
  }

  return *this;
}

template <typename T> shared_ptr<T>::~shared_ptr() {
  std::cout << "Removed obj" << std::endl;
  std::cout << "Counter: " << *counter << std::endl;

  if (storage != nullptr) {
    --(*counter);

    if (*counter == 0) {
      std::cout << "Removed ptr" << std::endl;
      delete storage;
    }
  }
}

template <typename T> bool shared_ptr<T>::isUnique() { return (counter == 1); }

template <typename T> size_t shared_ptr<T>::Count() { return *count; }

#endif SHARED_PTR

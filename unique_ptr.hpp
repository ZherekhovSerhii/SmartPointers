#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template <typename T> class unique_ptr {
public:
  unique_ptr(T *);
  ~unique_ptr();

  unique_ptr(const unique_ptr<T> &) = delete;
  unique_ptr &operator=(const unique_ptr<T> &) = delete;

  unique_ptr(unique_ptr<T> &&) noexcept;
  unique_ptr &operator=(unique_ptr<T> &&) noexcept;

private:
  T *storage;
};

template <typename T>
unique_ptr<T>::unique_ptr(T *ptr = nullptr) : storage(ptr) {
  std::cout << "Constructed" << std::endl;
}

template <typename T> unique_ptr<T>::~unique_ptr() {
  std::cout << "Removed obj" << std::endl;

  if (storage != nullptr) {
    std::cout << "Removed ptr" << std::endl;
    delete storage;
  }
}

template <typename T> unique_ptr<T>::unique_ptr(unique_ptr<T> &&raii) noexcept {
  std::cout << "Constructed move" << std::endl;

  if (raii.storage != nullptr) {
    storage = std::move(raii.storage);
    raii.storage = nullptr;
  }
}

template <typename T>
unique_ptr<T> &unique_ptr<T>::operator=(unique_ptr<T> &&raii) noexcept {
  if (this != &raii) {
    if (storage != nullptr) {
      std::cout << "Removed ptr" << std::endl;
      delete storage;
    }

    storage = std::move(raii.storage);
    raii.storage = nullptr;
  }

  return *this;
}

#endif UNIQUE_PTR
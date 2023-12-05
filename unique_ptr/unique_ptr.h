#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

// #define MAKE_UNIQUE_IMPLEMENTED

#include <memory>

template <class T>
class UniquePtr {
 private:
  T* ptr_ = nullptr;

 public:
  UniquePtr() = default;
  explicit UniquePtr(T* ptr) noexcept : ptr_(ptr){};
  UniquePtr(const UniquePtr<T>&) = delete;
  UniquePtr& operator=(const UniquePtr&) = delete;
  UniquePtr(UniquePtr&& other) noexcept {
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
  }
  UniquePtr<T>& operator=(UniquePtr<T>&& other) noexcept {
    delete ptr_;
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
    return *this;
  }
  T* Release() noexcept {
    auto copy = ptr_;
    ptr_ = nullptr;
    return copy;
  }
  void Reset(T* ptr = nullptr) noexcept {
    delete ptr_;
    ptr_ = ptr;
  }
  void Swap(UniquePtr<T>& other) noexcept {
    auto copy = ptr_;
    ptr_ = other.ptr_;
    other.ptr_ = copy;
  }
  T* Get() const noexcept {
    return ptr_;
  }
  T& operator*() const {
    return *ptr_;
  }
  T* operator->() const noexcept {
    return ptr_;
  }
  explicit operator bool() const noexcept {
    return ptr_ != nullptr;
  }
  ~UniquePtr() {
    delete ptr_;
  }
};

template <class T, class... Args>
UniquePtr<T> MakeUnique(Args&&... args) {
  return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

#endif
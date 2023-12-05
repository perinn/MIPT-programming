#pragma once

#include <memory>
#include <stdexcept>

class BadAnyCast : public std::bad_cast {
 public:
  [[nodiscard]] const char* what() const noexcept override {
    return "BadAnyCast error";
  }
};

class IHolder {
 public:
  virtual std::shared_ptr<IHolder> Clone() = 0;
};

template <class T>
class AnyHolder : public IHolder {
 public:
  T val;

  AnyHolder(const T& obj) : val(obj) {  //  NOLINT
  }

  std::shared_ptr<IHolder> Clone() override {
    std::shared_ptr<AnyHolder<T>> new_ptr(std::make_shared<AnyHolder<T>>(this->val));
    return new_ptr;
  }
};

class Any {
 public:
  std::shared_ptr<IHolder> ptr;

  Any() : ptr(nullptr) {
  }

  Any(const Any& other) : ptr(other.ptr->Clone()) {
  }

  Any(Any&& other) noexcept : ptr(std::move(other.ptr)) {
    other.ptr = nullptr;
  }

  template <class T>
  Any(const T& obj) : ptr(new AnyHolder<T>(obj)) {  //  NOLINT
  }

  Any& operator=(const Any& other) {
    if (this != &other) {
      Any(other).Swap(*this);
    }
    return *this;
  }

  Any& operator=(Any&& other) {
    if (this != &other) {
      this->ptr = other.ptr;
      other.ptr = nullptr;
    }
    return *this;
  }

  [[nodiscard]] bool HasValue() const {
    return static_cast<bool>(this->ptr);
  }

  void Reset() {
    this->ptr = nullptr;
  }

  void Swap(Any& second) {
    this->ptr.swap(second.ptr);
  }
};

template <class T>
T AnyCast(const Any& obj) {
  auto tmp = std::dynamic_pointer_cast<AnyHolder<T>>(obj.ptr);
  if (tmp) {
    return tmp->val;
  }
  throw BadAnyCast{};
}
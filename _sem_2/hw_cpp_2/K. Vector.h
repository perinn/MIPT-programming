#ifndef VECTOR_H
#define VECTOR_H
#define VECTOR_MEMORY_IMPLEMENTED

#include <iterator>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <exception>

template <typename T>
class Vector {
 private:
  T* container_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 0;
  template <class Iter>
  using EnableIfForwardIter = std::enable_if_t<
      std::is_base_of_v<std::forward_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>>;

 public:
  using ValueType = T;
  using Pointer = T*;
  using ConstPointer = const T*;
  using Reference = T&;
  using ConstReference = const T&;
  using SizeType = size_t;
  using Iterator = Pointer;
  using ConstIterator = ConstPointer;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

  Vector() noexcept = default;

  explicit Vector(size_t size) {
    container_ = nullptr;
    size_ = 0;
    capacity_ = 0;
    size_t i = 0;
    try {
      if (size != 0) {
        size_ = size;
        capacity_ = size_;
        container_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
        while (i < capacity_) {
          new (container_ + i) T;
          ++i;
        }
      }
    } catch (...) {
      if (container_ != nullptr) {
        for (size_t j = i; j >= 1; --j) {
          (container_ + j - 1)->~T();
        }
        operator delete(container_);
      }
      container_ = nullptr;
      size_ = 0;
      capacity_ = 0;
      throw;
    }
  }

  Vector(size_t size, const T& value) {
    container_ = nullptr;
    size_ = 0;
    capacity_ = 0;
    size_t i = 0;
    try {
      if (size != 0) {
        size_ = size;
        capacity_ = size_;
        container_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
        while (i < capacity_) {
          new (container_ + i) T(value);
          ++i;
        }
      }
    } catch (...) {
      if (container_ != nullptr) {
        for (size_t j = i; j >= 1; --j) {
          (container_ + j - 1)->~T();
        }
        operator delete(container_);
      }
      container_ = nullptr;
      size_ = 0;
      capacity_ = 0;
      throw;
    }
  }

  template <typename InputIterator, typename = EnableIfForwardIter<InputIterator>>
  Vector(InputIterator begin, InputIterator end) {
    container_ = nullptr;
    size_ = 0;
    capacity_ = 0;
    size_t i = 0;
    try {
      if (end != begin) {
        size_ = end - begin;
        capacity_ = end - begin;
        container_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
        while (begin != end) {
          new (container_ + i) T(*begin);
          ++begin;
          ++i;
        }
      }
    } catch (...) {
      if (container_ != nullptr) {
        for (size_t j = i; j >= 1; --j) {
          (container_ + j - 1)->~T();
        }
        operator delete(container_);
      }
      container_ = nullptr;
      size_ = 0;
      capacity_ = 0;
      throw;
    }
  }

  Vector(const std::initializer_list<T>& init_lst) {
    auto begin = init_lst.begin();
    auto end = init_lst.end();
    container_ = nullptr;
    size_ = 0;
    capacity_ = 0;
    size_t i = 0;
    try {
      if (end != begin) {
        size_ = end - begin;
        capacity_ = end - begin;
        container_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
        while (begin != end) {
          new (container_ + i) T(*begin);
          ++begin;
          ++i;
        }
      }
    } catch (...) {
      if (container_ != nullptr) {
        for (size_t j = i; j >= 1; --j) {
          (container_ + j - 1)->~T();
        }
        operator delete(container_);
      }
      container_ = nullptr;
      size_ = 0;
      capacity_ = 0;
      throw;
    }
  }

  Vector(const Vector& another) {
    size_t i = 0;
    try {
      while (i < size_) {
        (container_ + i)->~T();
        ++i;
      }
      operator delete(container_);
      container_ = nullptr;
      if (another.container_ == nullptr) {
        size_ = 0;
        capacity_ = 0;
        return;
      }
      capacity_ = another.capacity_;
      size_ = another.size_;
      container_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
      i = 0;
      while (i < size_) {
        new (container_ + i) T(another.container_[i]);
        ++i;
      }
    } catch (...) {
      if (container_ != nullptr) {
        for (size_t j = i; j >= 1; --j) {
          (container_ + j - 1)->~T();
        }
        operator delete(container_);
      }
      size_ = 0;
      capacity_ = 0;
      container_ = nullptr;
      throw;
    }
  }

  Vector(Vector&& another) noexcept
      : container_(std::exchange(another.container_, nullptr))
      , size_(std::exchange(another.size_, 0))
      , capacity_(std::exchange(another.capacity_, 0)) {
  }

  Vector& operator=(const Vector& another) {
    if (this != &another) {
      auto backup_container = std::exchange(container_, nullptr);
      auto backup_size = std::exchange(size_, 0);
      auto backup_capacity = std::exchange(capacity_, 0);
      try {
        Vector(another).Swap(*this);
        for (size_t i = 0; i < backup_size; i++) {
          (backup_container + i)->~T();
        }
        operator delete(backup_container);
      } catch (...) {
        container_ = backup_container;
        size_ = backup_size;
        capacity_ = backup_capacity;
        throw;
      }
    }
    return *this;
  }

  Vector& operator=(Vector&& another) noexcept {
    if (this != &another) {
      Vector(std::move(another)).Swap(*this);
    }
    return *this;
  }

  ~Vector() noexcept(std::is_nothrow_destructible_v<ValueType>) {
    for (size_t i = 0; i < size_; ++i) {
      (container_ + i)->~T();
    }
    operator delete(container_);
    container_ = nullptr;
  }

  [[nodiscard]] SizeType Size() const noexcept {
    return size_;
  }

  [[nodiscard]] SizeType Capacity() const noexcept {
    return capacity_;
  }

  [[nodiscard]] bool Empty() const noexcept {
    return size_ == 0;
  }

  [[nodiscard]] ConstReference operator[](size_t index) const noexcept {
    return container_[index];
  }

  [[nodiscard]] Reference operator[](size_t index) noexcept {
    return container_[index];
  }

  [[nodiscard]] ConstReference At(size_t index) const {
    if (index >= size_) {
      throw std::out_of_range("");
    }
    return (*this)[index];
  }

  [[nodiscard]] Reference At(size_t index) {
    if (index >= size_) {
      throw std::out_of_range("");
    }
    return (*this)[index];
  }

  [[nodiscard]] ConstReference Front() const noexcept {
    return container_[0];
  }

  [[nodiscard]] Reference Front() noexcept {
    return container_[0];
  }

  [[nodiscard]] ConstReference Back() const noexcept {
    return container_[size_ - 1];
  }

  [[nodiscard]] Reference Back() noexcept {
    return container_[size_ - 1];
  }

  [[nodiscard]] ConstPointer Data() const noexcept {
    return container_;
  }

  [[nodiscard]] Pointer Data() noexcept {
    return container_;
  }

  void Swap(Vector& another) noexcept {
    std::swap(container_, another.container_);
    std::swap(size_, another.size_);
    std::swap(capacity_, another.capacity_);
  }

  void Resize(size_t size) {
    auto backup_container = container_;
    auto backup_size = size_;
    auto backup_capacity = capacity_;
    try {
      if (!(size > capacity_)) {
        if (size > size_) {
          for (size_t i = size_; i < size; ++i) {
            new (container_ + i) T;
          }
          size_ = size;
          return;
        }
        for (size_t i = size; i < size_; ++i) {
          (container_ + i)->~T();
        }
      } else {
        container_ = nullptr;
        capacity_ = size;
        if (!(backup_container == nullptr)) {
          size_t i = 0;
          try {
            container_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
            while (i < size) {
              new (container_ + i) T;
              ++i;
            }
          } catch (...) {
            if (container_ != nullptr) {
              for (size_t j = i; j >= 1; --j) {
                (container_ + j - 1)->~T();
              }
              operator delete(container_);
            }
            container_ = nullptr;
            throw;
          }
          for (i = 0; i < backup_size; ++i) {
            *(container_ + i) = T(std::move(backup_container[i]));
          }
          for (i = 0; i < backup_size; ++i) {
            (backup_container + i)->~T();
          }
          operator delete(backup_container);
        } else {
          size_t i = 0;
          try {
            container_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
            while (i < size) {
              new (container_ + i) T;
              ++i;
            }
          } catch (...) {
            if (container_ != nullptr) {
              for (size_t j = i; j >= 1; --j) {
                (container_ + j - 1)->~T();
              }
              operator delete(container_);
            }
            container_ = nullptr;
            throw;
          }
        }
      }
      size_ = size;
    } catch (...) {
      if (container_ != nullptr) {
        for (size_t i = 0; i < capacity_; ++i) {
          (container_ + i)->~T();
        }
        operator delete(container_);
      }
      container_ = backup_container;
      size_ = backup_size;
      capacity_ = backup_capacity;
      throw;
    }
  }

  void Resize(size_t size, const T& value) {
    auto backup_container = container_;
    auto backup_size = size_;
    auto backup_capacity = capacity_;
    if (size_ == size) {
      return;
    }
    try {
      if (!(size > capacity_)) {
        if (!(size > size_)) {
          for (size_t i = size; i < size_; ++i) {
            (container_ + i)->~T();
          }
        } else {
          try {
            for (size_t i = size_; i < size; ++i) {
              *(container_ + i) = T(value);
            }
          } catch (...) {
            container_ = nullptr;
          }
        }
      } else {
        container_ = nullptr;
        capacity_ = size;
        if (!(backup_container == nullptr)) {
          size_t i = 0;
          try {
            container_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
            while (i < size) {
              new (container_ + i) T;
              ++i;
            }
          } catch (...) {
            if (container_ != nullptr) {
              for (size_t j = i; j >= 1; --j) {
                (container_ + j - 1)->~T();
              }
              operator delete(container_);
            }
            container_ = nullptr;
            throw;
          }
          for (i = backup_size; i < size; ++i) {
            *(container_ + i) = T(value);
          }
          for (i = 0; i < backup_size; ++i) {
            *(container_ + i) = T(std::move(backup_container[i]));
          }
          for (i = 0; i < backup_size; ++i) {
            (backup_container + i)->~T();
          }
          operator delete(backup_container);
        } else {
          size_t i = 0;
          try {
            container_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
            while (i < size) {
              new (container_ + i) T(value);
              ++i;
            }
          } catch (...) {
            if (container_ != nullptr) {
              for (size_t j = i; j >= 1; --j) {
                (container_ + j - 1)->~T();
              }
              operator delete(container_);
            }
            container_ = nullptr;
            throw;
          }
        }
      }
      size_ = size;
    } catch (...) {
      if (container_ != nullptr) {
        for (size_t i = 0; i < capacity_; ++i) {
          (container_ + i)->~T();
        }
        operator delete(container_);
      }
      container_ = backup_container;
      size_ = backup_size;
      capacity_ = backup_capacity;
      throw;
    }
  }

  void Reserve(size_t capacity) {
    if (capacity <= capacity_) {
      return;
    }
    auto backup_container = container_;
    auto backup_size = size_;
    auto backup_capacity = capacity_;
    try {
      capacity_ = capacity;
      container_ = nullptr;
      if (!(backup_container == nullptr)) {
        size_t i = 0;
        try {
          container_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
          while (i < size_) {
            new (container_ + i) T;
            ++i;
          }
        } catch (...) {
          if (container_ != nullptr) {
            for (size_t j = i; j >= 1; --j) {
              (container_ + j - 1)->~T();
            }
            operator delete(container_);
          }
          container_ = nullptr;
          throw;
        }
        for (i = 0; i < backup_size; ++i) {
          *(container_ + i) = T(std::move(backup_container[i]));
        }
        for (i = 0; i < backup_size; ++i) {
          (backup_container + i)->~T();
        }
        operator delete(backup_container);
      } else {
        size_t i = 0;
        try {
          container_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
        } catch (...) {
          if (container_ != nullptr) {
            for (size_t j = i; j >= 1; --j) {
              (container_ + j - 1)->~T();
            }
            operator delete(container_);
          }
          container_ = nullptr;
          throw;
        }
      }
    } catch (...) {
      if (container_ != nullptr) {
        for (size_t i = 0; i < capacity_; ++i) {
          (container_ + i)->~T();
        }
        operator delete(container_);
      }
      container_ = backup_container;
      size_ = backup_size;
      capacity_ = backup_capacity;
      throw;
    }
  }

  void ShrinkToFit() {
    if (capacity_ == size_) {
      return;
    }
    if (size_ == 0) {
      try {
        capacity_ = size_;
        operator delete(container_);
        container_ = nullptr;
        return;
      } catch (...) {
        container_ = nullptr;
        throw;
      }
    }
    auto backup_container = container_;
    auto backup_size = size_;
    auto backup_capacity = capacity_;
    container_ = nullptr;
    try {
      capacity_ = size_;
      size_t i = 0;
      try {
        container_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
        while (i < backup_size) {
          new (container_ + i) T;
          ++i;
        }
      } catch (...) {
        if (container_ != nullptr) {
          for (size_t j = i; j >= 1; --j) {
            (container_ + j - 1)->~T();
          }
          operator delete(container_);
        }
        container_ = nullptr;
        throw;
      }
      for (i = 0; i < backup_size; ++i) {
        *(container_ + i) = T(std::move(backup_container[i]));
      }
      for (i = 0; i < backup_size; ++i) {
        (backup_container + i)->~T();
      }
      operator delete(backup_container);
    } catch (...) {
      if (container_ != nullptr) {
        for (size_t i = 0; i < capacity_; ++i) {
          (container_ + i)->~T();
        }
        operator delete(container_);
      }
      container_ = backup_container;
      size_ = backup_size;
      capacity_ = backup_capacity;
      throw;
    }
  }

  void Clear() {
    for (size_t i = 0; i < size_; ++i) {
      (container_ + i)->~T();
    }
    size_ = 0;
    operator delete(container_);
    container_ = nullptr;
    capacity_ = 0;
  }

  void PushBack(const T& value) {
    auto backup_container = container_;
    auto backup_size = size_;
    auto backup_capacity = capacity_;
    if (capacity_ > size_) {
      new (container_ + size_) T(value);
      ++size_;
      return;
    }
    try {
      if (!(capacity_ == 0)) {
        capacity_ *= 2;
      } else {
        capacity_ = 1;
      }
      container_ = nullptr;
      size_t i = 0;
      try {
        container_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
        while (i < size_ + 1) {
          new (container_ + i) T;
          ++i;
        }
      } catch (...) {
        if (container_ != nullptr) {
          for (size_t j = i; j >= 1; --j) {
            (container_ + j - 1)->~T();
          }
          operator delete(container_);
        }
        container_ = nullptr;
        throw;
      }
      for (i = 0; i < backup_size; ++i) {
        *(container_ + i) = T(std::move(backup_container[i]));
      }
      *(container_ + size_) = T(value);
      ++size_;
      for (i = 0; i < backup_size; ++i) {
        (backup_container + i)->~T();
      }
      operator delete(backup_container);
    } catch (...) {
      if (container_ != nullptr) {
        for (size_t i = 0; i < capacity_; ++i) {
          (container_ + i)->~T();
        }
        operator delete(container_);
      }
      container_ = backup_container;
      size_ = backup_size;
      capacity_ = backup_capacity;
      throw;
    }
  }

  void PushBack(T&& value) {
    auto backup_container = container_;
    auto backup_size = size_;
    auto backup_capacity = capacity_;
    if (capacity_ > size_) {
      new (container_ + size_) T(std::move(value));
      ++size_;
      return;
    }
    try {
      if (!(capacity_ == 0)) {
        capacity_ *= 2;
      } else {
        capacity_ = 1;
      }
      container_ = nullptr;
      size_t i = 0;
      try {
        container_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
        while (i < size_ + 1) {
          new (container_ + i) T;
          ++i;
        }
      } catch (...) {
        if (container_ != nullptr) {
          for (size_t j = i; j >= 1; --j) {
            (container_ + j - 1)->~T();
          }
          operator delete(container_);
        }
        container_ = nullptr;
        throw;
      }
      for (i = 0; i < backup_size; ++i) {
        *(container_ + i) = T(std::move(backup_container[i]));
      }
      *(container_ + size_) = T(std::move(value));
      ++size_;
      for (i = 0; i < backup_size; ++i) {
        (backup_container + i)->~T();
      }
      operator delete(backup_container);
    } catch (...) {
      if (container_ != nullptr) {
        for (size_t i = 0; i < capacity_; ++i) {
          (container_ + i)->~T();
        }
        operator delete(container_);
      }
      container_ = backup_container;
      size_ = backup_size;
      capacity_ = backup_capacity;
      throw;
    }
  }

  void PopBack() noexcept(std::is_nothrow_destructible_v<ValueType>) {
    auto backup_container = container_;
    auto backup_size = size_;
    auto backup_capacity = capacity_;
    try {
      if (size_ == 0) {
        return;
      }
      --size_;
      (container_ + size_)->~T();
    } catch (...) {
      container_ = backup_container;
      size_ = backup_size;
      capacity_ = backup_capacity;
    }
  }

  template <typename... Args>
  void EmplaceBack(Args... args) {
    auto backup_container = container_;
    auto backup_size = size_;
    auto backup_capacity = capacity_;
    if (capacity_ > size_) {
      new (container_ + size_) T(std::forward<Args>(args)...);
      ++size_;
      return;
    }
    try {
      if (!(capacity_ == 0)) {
        capacity_ *= 2;
      } else {
        capacity_ = 1;
      }
      container_ = nullptr;
      size_t i = 0;
      try {
        container_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
        while (i < size_ + 1) {
          new (container_ + i) T;
          ++i;
        }
      } catch (...) {
        if (container_ != nullptr) {
          for (size_t j = i; j >= 1; --j) {
            (container_ + j - 1)->~T();
          }
          operator delete(container_);
        }
        container_ = nullptr;
        throw;
      }
      for (i = 0; i < backup_size; ++i) {
        *(container_ + i) = T(std::move(backup_container[i]));
      }
      *(container_ + size_) = T(std::forward<Args>(args)...);
      ++size_;
      for (i = 0; i < backup_size; ++i) {
        (backup_container + i)->~T();
      }
      operator delete(backup_container);
    } catch (...) {
      if (container_ != nullptr) {
        for (size_t i = 0; i < capacity_; ++i) {
          (container_ + i)->~T();
        }
        operator delete(container_);
      }
      container_ = backup_container;
      size_ = backup_size;
      capacity_ = backup_capacity;
      throw;
    }
  }

  [[nodiscard]] ConstIterator begin() const noexcept {  // NOLINT
    return cbegin();
  }

  [[nodiscard]] Iterator begin() noexcept {  // NOLINT
    return Data();
  }

  [[nodiscard]] ConstIterator end() const noexcept {  // NOLINT
    return cend();
  }

  [[nodiscard]] Iterator end() noexcept {  // NOLINT
    return size_ + Data();
  }

  [[nodiscard]] ConstIterator cbegin() const noexcept {  // NOLINT
    return Data();
  }

  [[nodiscard]] ConstIterator cend() const noexcept {  // NOLINT
    return size_ + Data();
  }

  [[nodiscard]] ConstReverseIterator rbegin() const noexcept {  // NOLINT
    return crbegin();
  }

  [[nodiscard]] ReverseIterator rbegin() noexcept {  // NOLINT
    return ReverseIterator(end());
  }

  [[nodiscard]] ConstReverseIterator rend() const noexcept {  // NOLINT
    return crend();
  }

  [[nodiscard]] ReverseIterator rend() noexcept {  // NOLINT
    return ReverseIterator(begin());
  }

  [[nodiscard]] ConstReverseIterator crbegin() const noexcept {  // NOLINT
    return ConstReverseIterator(cend());
  }

  [[nodiscard]] ConstReverseIterator crend() const noexcept {  // NOLINT
    return ConstReverseIterator(cbegin());
  }
};

template <typename T>
[[nodiscard]] bool operator<(const Vector<T>& a, const Vector<T>& b) noexcept {
  if (a.Empty() && b.Empty()) {
    return false;
  }
  if (a.Empty()) {
    return true;
  }
  if (b.Empty()) {
    return false;
  }
  size_t n = std::min(b.Size(), a.Size());
  size_t i = 0;
  bool flag = false;
  for (; i < n; ++i) {
    if (a.Data()[i] != b.Data()[i]) {
      flag = true;
      break;
    }
  }
  if (!flag && b.Size() <= a.Size()) {
    return false;
  }
  if (!flag && b.Size() > a.Size()) {
    return true;
  }
  return a.Data()[i] < b.Data()[i];
}

template <typename T>
[[nodiscard]] inline bool operator>(const Vector<T>& a, const Vector<T>& b) noexcept {
  return !(a <= b);
}

template <typename T>
[[nodiscard]] inline bool operator<=(const Vector<T>& a, const Vector<T>& b) noexcept {
  return (a < b || a == b);
}

template <typename T>
[[nodiscard]] inline bool operator>=(const Vector<T>& a, const Vector<T>& b) noexcept {
  return !(a < b);
}

template <typename T>
[[nodiscard]] bool operator==(const Vector<T>& a, const Vector<T>& b) noexcept {
  if (a.Size() != b.Size()) {
    return false;
  }
  if (a.Data() == nullptr) {
    return true;
  }
  for (size_t i = 0; i < a.Size(); ++i) {
    if (a.Data()[i] != b.Data()[i]) {
      return false;
    }
  }
  return true;
}

template <typename T>
[[nodiscard]] inline bool operator!=(const Vector<T>& a, const Vector<T>& b) noexcept {
  return !(a == b);
}

#endif
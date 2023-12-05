#include "cppstring.h"

String::String() : buffer_(nullptr), size_(0), capacity_(1) {
}

String::String(const size_t& size, const char& symb) {
  if (size != 0) {
    buffer_ = new char[size + 1];
    for (size_t i = 0; i < size; ++i) {
      buffer_[i] = symb;
    }
    buffer_[size] = '\0';
  } else {
    buffer_ = nullptr;
  }
  size_ = size;
  capacity_ = size + 1;
}

size_t LenStr(const char* c_str) {
  size_t size = 0, i = 0;
  if (c_str != nullptr) {
    while (c_str[i++] != '\0') {
      ++size;
    }
  }
  return size;
}

String::String(const char* c_str) {
  size_t size = LenStr(c_str);
  if (size != 0) {
    buffer_ = new char[size + 1];
    for (size_t i = 0; i < size; ++i) {
      buffer_[i] = c_str[i];
    }
    buffer_[size] = '\0';
  } else {
    buffer_ = nullptr;
  }
  size_ = size;
  capacity_ = size + 1;
}

String::String(const String& other) {
  if (other.size_ != 0) {
    buffer_ = new char[other.size_ + 1];
    for (size_t i = 0; i < other.size_; ++i) {
      buffer_[i] = other.buffer_[i];
    }
    buffer_[other.size_] = '\0';
  } else {
    buffer_ = nullptr;
  }
  size_ = other.size_;
  capacity_ = other.size_ + 1;
}

String::String(const char* c_str, const size_t& size) {
  if (size != 0) {
    buffer_ = new char[size + 1];
    for (size_t i = 0; i < size; ++i) {
      buffer_[i] = c_str[i];
    }
    buffer_[size] = '\0';
  } else {
    buffer_ = nullptr;
  }
  size_ = size;
  capacity_ = size + 1;
}

String::~String() {
  delete[] buffer_;
}

char String::operator[](const size_t& idx) const {
  return buffer_[idx];
}

char& String::operator[](const size_t& idx) {
  return buffer_[idx];
}

char String::At(const size_t& idx) const {
  if (idx > size_ - 1) {
    throw StringOutOfRange{};
  }
  return buffer_[idx];
}

char& String::At(const size_t& idx) {
  if (idx > size_ - 1) {
    throw StringOutOfRange{};
  }
  return buffer_[idx];
}

char String::Front() const {
  return buffer_[0];
}

char& String::Front() {
  return buffer_[0];
}

char String::Back() const {
  return buffer_[size_ - 1];
}

char& String::Back() {
  return buffer_[size_ - 1];
}

char* String::CStr() {
  return buffer_;
}

const char* String::CStr() const {
  return buffer_;
}

char* String::Data() {
  return buffer_;
}

const char* String::Data() const {
  return buffer_;
}

bool String::Empty() const {
  return size_ == 0;
}

size_t String::Size() const {
  return size_;
}

size_t String::Length() const {
  return size_;
}

size_t String::Capacity() const {
  return capacity_ - 1;
}

void String::Clear() {
  size_ = 0;
}

void String::Swap(String& second) {
  String temp_str(buffer_);
  *this = second;
  second = temp_str;
}

void String::PopBack() {
  --size_;
}

char* UpSize(const char* c_str, size_t current_size, size_t& capacity) {
  auto tmp_buffer = new char[(capacity - 1) * 2 + 1];
  for (size_t i = 0; i < current_size; ++i) {
    tmp_buffer[i] = c_str[i];
  }
  tmp_buffer[current_size] = '\0';
  capacity = (capacity - 1) * 2 + 1;
  delete[] c_str;
  return tmp_buffer;
}

char* UpCapacity(const char* c_str, size_t current_size, size_t& capacity, size_t new_capacity) {
  auto tmp_buffer = new char[new_capacity + 1];
  if (new_capacity >= current_size) {
    for (size_t i = 0; i < current_size; ++i) {
      tmp_buffer[i] = c_str[i];
    }
    tmp_buffer[current_size] = '\0';
  } else {
    for (size_t i = 0; i < new_capacity; ++i) {
      tmp_buffer[i] = c_str[i];
    }
    tmp_buffer[new_capacity] = '\0';
  }
  capacity = new_capacity + 1;
  delete[] c_str;
  return tmp_buffer;
}

void String::PushBack(const char& symb) {
  if (buffer_ != nullptr) {
    if (size_ == capacity_ - 1) {
      buffer_ = UpSize(buffer_, size_, capacity_);
    }
    buffer_[size_] = symb;
    ++size_;
  } else {
    buffer_ = new char[2];
    buffer_[0] = symb;
    buffer_[1] = '\0';
    size_ = 1;
    capacity_ = 2;
  }
}

String& String::operator+=(const String& second) {
  size_t size = LenStr(second.buffer_);
  if (size != 0) {
    if (capacity_ == 1) {
      buffer_ = new char[size + 1];
      for (size_t i = 0; i < size; ++i) {
        buffer_[i] = second.buffer_[i];
      }
      buffer_[size] = '\0';
      size_ = size;
      capacity_ = size + 1;
    } else {
      while (size_ + size > capacity_ - 1) {
        buffer_ = UpSize(buffer_, size_, capacity_);
      }
      for (size_t i = size_; i < size_ + size; ++i) {
        buffer_[i] = second.buffer_[i - size_];
      }
      buffer_[size_ + size] = '\0';
      size_ += size;
    }
  }
  return *this;
}

void String::Resize(const size_t& new_size, const char& symb) {
  if (capacity_ != 1) {
    if (new_size <= capacity_) {
      if (new_size <= size_) {
        size_ = new_size;
      } else {
        for (size_t i = size_; i < new_size; ++i) {
          buffer_[i] = symb;
        }
        size_ = new_size;
      }
    } else {
      while (capacity_ - 1 < new_size) {
        buffer_ = UpSize(buffer_, size_, capacity_);
      }
      for (size_t i = size_; i < new_size; ++i) {
        buffer_[i] = symb;
      }
      size_ = new_size;
    }
  } else {
    buffer_ = new char[new_size + 1];
    for (size_t i = 0; i < new_size; ++i) {
      buffer_[i] = symb;
    }
    size_ = new_size;
    capacity_ = new_size + 1;
  }
}

void String::Reserve(const size_t& new_capacity) {
  size_t max_capacity = std::max(capacity_, new_capacity);
  if (max_capacity != capacity_) {
    buffer_ = UpCapacity(buffer_, size_, capacity_, new_capacity);
  }
}

void String::ShrinkToFit() {
  buffer_ = UpCapacity(buffer_, size_, capacity_, size_);
}

std::ostream& operator<<(std::ostream& out, const String& str) {
  if (str.buffer_ != nullptr) {
    size_t i = 0;
    while (str.buffer_[i++] != '\0') {
      out << str.buffer_[i - 1];
    }
  }
  return out;
}

const String operator+(const String& first, const String& second) {
  String new_str(first);
  new_str += second;
  return new_str;
}

bool String::operator>(const String& second) const {
  size_t max_size = std::max(size_, second.size_);
  bool flag = false;
  size_t counter = 0;
  if (max_size != size_) {
    for (size_t i = 0; i < size_; ++i) {
      if (buffer_[i] > second.buffer_[i]) {
        flag = true;
        break;
      }
      if (buffer_[i] < second.buffer_[i]) {
        break;
      }
    }
  } else {
    for (size_t i = 0; i < second.size_; ++i) {
      if (buffer_[i] > second.buffer_[i]) {
        flag = true;
        break;
      }
      if (buffer_[i] < second.buffer_[i]) {
        break;
      }
      ++counter;
    }
    if (counter == second.size_) {
      if (max_size != second.size_) {
        flag = true;
      }
    }
  }
  return flag;
}

bool String::operator<(const String& second) const {
  size_t max_size = std::max(size_, second.size_);
  bool flag = false;
  size_t counter = 0;
  if (max_size != size_) {
    for (size_t i = 0; i < size_; ++i) {
      if (buffer_[i] < second.buffer_[i]) {
        flag = true;
        break;
      }
      if (buffer_[i] > second.buffer_[i]) {
        break;
      }
      ++counter;
    }
    if (counter == size_) {
      if (max_size != size_) {
        flag = true;
      }
    }
  } else {
    for (size_t i = 0; i < second.size_; ++i) {
      if (buffer_[i] < second.buffer_[i]) {
        flag = true;
        break;
      }
      if (buffer_[i] > second.buffer_[i]) {
        break;
      }
    }
  }
  return flag;
}

bool String::operator>=(const String& second) const {
  size_t max_size = std::max(size_, second.size_);
  bool flag = false;
  size_t counter = 0;
  if (max_size != size_) {
    for (size_t i = 0; i < size_; ++i) {
      if (buffer_[i] > second.buffer_[i]) {
        flag = true;
        break;
      }
      if (buffer_[i] < second.buffer_[i]) {
        break;
      }
      ++counter;
    }
    if (counter == size_) {
      if (max_size == size_) {
        flag = true;
      }
    }
  } else {
    for (size_t i = 0; i < second.size_; ++i) {
      if (buffer_[i] > second.buffer_[i]) {
        flag = true;
        break;
      }
      if (buffer_[i] < second.buffer_[i]) {
        break;
      }
      ++counter;
    }
    if (counter == second.size_) {
      flag = true;
    }
  }
  return flag;
}

bool String::operator<=(const String& second) const {
  size_t max_size = std::max(size_, second.size_);
  bool flag = false;
  size_t counter = 0;
  if (max_size != size_) {
    for (size_t i = 0; i < size_; ++i) {
      if (buffer_[i] < second.buffer_[i]) {
        flag = true;
        break;
      }
      if (buffer_[i] > second.buffer_[i]) {
        break;
      }
      ++counter;
    }
    if (counter == size_) {
      flag = true;
    }
  } else {
    for (size_t i = 0; i < second.size_; ++i) {
      if (buffer_[i] < second.buffer_[i]) {
        flag = true;
        break;
      }
      if (buffer_[i] > second.buffer_[i]) {
        break;
      }
      ++counter;
    }
    if (counter == second.size_) {
      if (max_size == second.size_) {
        flag = true;
      }
    }
  }
  return flag;
}

bool String::operator==(const String& second) const {
  bool flag = true;
  if (size_ != second.size_) {
    flag = false;
  } else {
    for (size_t i = 0; i < size_; ++i) {
      if (buffer_[i] != second.buffer_[i]) {
        flag = false;
        break;
      }
    }
  }
  return flag;
}

bool String::operator!=(const String& second) const {
  size_t max_size = std::max(size_, second.size_);
  bool flag = false;
  size_t counter = 0;
  if (max_size != size_) {
    for (size_t i = 0; i < size_; ++i) {
      if (buffer_[i] != second.buffer_[i]) {
        flag = true;
        break;
      }
      ++counter;
    }
    if (counter == size_) {
      if (size_ != max_size) {
        flag = true;
      }
    }
  } else {
    for (size_t i = 0; i < second.size_; ++i) {
      if (buffer_[i] != second.buffer_[i]) {
        flag = true;
        break;
      }
      ++counter;
    }
    if (counter == second.size_) {
      if (second.size_ != max_size) {
        flag = true;
      }
    }
  }
  return flag;
}

String& String::operator=(const String& second) {
  if (second.buffer_ != nullptr) {
    size_t size = LenStr(second.buffer_);
    buffer_ = UpCapacity(buffer_, size_, capacity_, second.Capacity());
    for (size_t i = 0; i < size; ++i) {
      buffer_[i] = second.buffer_[i];
    }
    buffer_[size] = '\0';
    size_ = size;
    capacity_ = second.Capacity() + 1;
  } else {
    if (buffer_ != nullptr) {
      delete[] buffer_;
      buffer_ = nullptr;
    }
    size_ = 0;
    capacity_ = 1;
  }
  return *this;
}
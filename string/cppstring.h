#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <stdexcept>

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

class String {
 private:
  char* buffer_;
  size_t size_;
  size_t capacity_;

 public:
  String();
  String(const size_t&, const char&);
  String(const char*);    //  NOLINT
  String(const String&);  //  NOLINT
  String(const char*, const size_t&);
  ~String();
  String& operator=(const String&);
  friend char* UpSize(const char*, size_t, size_t&);
  char operator[](const size_t&) const;
  char& operator[](const size_t&);
  char At(const size_t&) const;
  char& At(const size_t&);
  char Front() const;
  char& Front();
  char Back() const;
  char& Back();
  char* CStr();
  const char* CStr() const;
  char* Data();
  const char* Data() const;
  bool Empty() const;
  size_t Size() const;
  size_t Length() const;
  size_t Capacity() const;
  void Clear();
  void Swap(String&);
  void PopBack();
  void PushBack(const char&);
  String& operator+=(const String&);
  friend const String operator+(const String&, const String&);
  bool operator>(const String&) const;
  bool operator<(const String&) const;
  bool operator>=(const String&) const;
  bool operator<=(const String&) const;
  bool operator==(const String&) const;
  bool operator!=(const String&) const;
  friend std::ostream& operator<<(std::ostream&, const String&);
  void Resize(const size_t&, const char&);
  void Reserve(const size_t&);
  void ShrinkToFit();
};

#endif
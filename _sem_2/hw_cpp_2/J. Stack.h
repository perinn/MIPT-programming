#include <iostream>
#include <queue>

#ifndef STACK_H
#define STACK_H

template <class T, class Container = std::deque<T>>
class Stack {
  Container body_;

 public:
  Stack() = default;

  explicit Stack(const Container& body) {
    body_ = Container(body.begin(), body.end());
  }

  template <class Iter>
  Stack(Iter begin, Iter end) {
    body_ = Container(begin, end);
  }

  const T& Top() const {
    return body_.back();
  }

  T& Top() {
    return body_.back();
  }

  bool Empty() const {
    return body_.empty();
  }

  size_t Size() const {
    return body_.size();
  }

  void Push(T&& val) {
    body_.push_back(std::move(val));
  }

  void Push(const T& val) {
    body_.push_back(val);
  }

  template <class... Args>
  void Emplace(Args&&... arguments) {
    body_.emplace_back(std::forward<Args>(arguments)...);
  }

  void Pop() {
    body_.pop_back();
  }

  void Swap(Stack& another) {
    std::swap(body_, another.body_);
  }
};

#endif
#pragma once

class Iterator {
 public:
  int64_t val_;
  int64_t step_;

  Iterator() {
    val_ = 0;
    step_ = 1;
  }

  bool operator==(Iterator& another) {
    return val_ == another.val_;
  }

  bool operator!=(Iterator& another) {
    return (val_ > another.val_ && step_ < 0) || (val_ < another.val_ && step_ > 0);
  }

  int64_t operator*() {
    return val_;
  }

  Iterator operator++() {
    Iterator copy;
    copy.val_ = val_ + step_;
    copy.step_ = step_;
    val_ += step_;
    return copy;
  }

  Iterator& operator++(int) {
    val_ += step_;
    return *this;
  }
};

class Range {
  Iterator begin_;
  Iterator end_;

 public:
  Range() {
    begin_ = Iterator();
    end_ = Iterator();
  }

  explicit Range(int64_t end) {
    if (end > 0) {
      begin_.val_ = 0;
      begin_.step_ = 1;
      end_.val_ = end;
      end_.step_ = 1;
    }
  }

  Range(int64_t begin, int64_t end, int64_t step = 1) {
    if ((end - begin > 0 && step > 0) || (end - begin < 0 && step < 0)) {
      begin_.val_ = begin;
      begin_.step_ = step;
      end_.val_ = end;
      end_.step_ = step;
    }
  }

  Iterator begin() {  // NOLINT
    return begin_;
  }

  Iterator end() {  // NOLINT
    return end_;
  }

  const Iterator begin() const {  // NOLINT
    return begin_;
  }

  const Iterator end() const {  // NOLINT
    return end_;
  }
};
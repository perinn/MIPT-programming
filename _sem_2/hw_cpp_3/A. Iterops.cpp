#ifndef ITEROPS
#define ITEROPS

#include <iostream>

template <typename IterType>
void Advance(IterType&, int64_t);

template <typename IterType>
IterType Next(IterType, int64_t);

template <typename IterType>
IterType Prev(IterType, int64_t);

template <typename IterType>
int64_t Distance(const IterType&, const IterType&);

template <typename IterType>
IterType Next(IterType);

template <typename IterType>
IterType Prev(IterType);

template <typename IterType>
void Advance(IterType& iter, int64_t cnt) {
  if constexpr (std::is_same_v<typename std::iterator_traits<IterType>::iterator_category,
                               std::bidirectional_iterator_tag>) {
    while (cnt < 0) {
      --iter;
      ++cnt;
    }
    while (cnt > 0) {
      ++iter;
      --cnt;
    }
  } else if constexpr (std::is_same_v<typename std::iterator_traits<IterType>::iterator_category,
                                      std::random_access_iterator_tag>) {
    iter = iter + cnt;
  } else {
    while (cnt > 0) {
      ++iter;
      --cnt;
    }
  }
}

template <typename IterType>
IterType Next(IterType iter, int64_t cnt) {
  if constexpr (std::is_same_v<typename std::iterator_traits<IterType>::iterator_category,
                               std::bidirectional_iterator_tag>) {
    while (cnt > 0) {
      ++iter;
      --cnt;
    }
    while (cnt < 0) {
      --iter;
      ++cnt;
    }
    return iter;
  }
  if constexpr (std::is_same_v<typename std::iterator_traits<IterType>::iterator_category,
                               std::random_access_iterator_tag>) {
    iter = iter + cnt;
    return iter;
  }
  while (cnt > 0) {
    ++iter;
    --cnt;
  }
  return iter;
}

template <typename IterType>
IterType Prev(IterType iter, int64_t cnt) {
  if constexpr (std::is_same_v<typename std::iterator_traits<IterType>::iterator_category,
                               std::bidirectional_iterator_tag>) {
    while (cnt > 0) {
      --iter;
      --cnt;
    }
    while (cnt < 0) {
      ++iter;
      ++cnt;
    }
    return iter;
  }
  if constexpr (std::is_same_v<typename std::iterator_traits<IterType>::iterator_category,
                               std::random_access_iterator_tag>) {
    iter = iter - cnt;
    return iter;
  }
  while (cnt > 0) {
    --iter;
    --cnt;
  }
  return iter;
}

template <typename IterType>
int64_t Distance(const IterType& iter_first, const IterType& iter_second) {
  if constexpr (std::is_same_v<typename std::iterator_traits<IterType>::iterator_category,
                               std::random_access_iterator_tag>) {
    return iter_second - iter_first;
  }
  int64_t cnt = 0;
  IterType tmp = iter_first;
  while (tmp != iter_second) {
    ++tmp;
    ++cnt;
  }
  return cnt;
}

template <typename IterType>
IterType Next(IterType iter) {
  return Next(iter, 1);
}

template <typename IterType>
IterType Prev(IterType iter) {
  return Prev(iter, 1);
}

#endif
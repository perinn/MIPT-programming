#ifndef ITEROPS
#define ITEROPS
#include <iostream>
template <class IteratorType>
void Advance(IteratorType& iterator, int n) {
  if constexpr (std::is_same_v<typename std::iterator_traits<IteratorType>::iterator_category,
                               std::random_access_iterator_tag>) {
    iterator = iterator + n;
  } else if constexpr (std::is_same_v<typename std::iterator_traits<IteratorType>::iterator_category,
                                      std::bidirectional_iterator_tag>) {
    if (n <= 0) {
      for (; n < 0; n++) {
        iterator--;
      }
    } else {
      for (; n > 0; iterator++) {
        n--;
      }
    }
  } else {
    for (; n > 0; iterator++) {
      --n;
    }
  }
}

template <class IteratorType>
IteratorType Next(IteratorType iterator, int n) {
  if constexpr (std::is_same_v<typename std::iterator_traits<IteratorType>::iterator_category,
                               std::random_access_iterator_tag>) {
    iterator = iterator + n;
    return iterator;
  } else if constexpr (std::is_same_v<typename std::iterator_traits<IteratorType>::iterator_category,
                                      std::bidirectional_iterator_tag>) {
    if (!(n <= 0)) {
      for (; n > 0; iterator++) {
        n--;
      }
      return iterator;
    }
    for (; n < 0; n++) {
      iterator--;
    }
    return iterator;
  }
  for (; n > 0; iterator++) {
    n--;
  }
  return iterator;
}

template <class IteratorType>
IteratorType Next(IteratorType iterator) {
  return Next(iterator, 1);
}

template <class IteratorType>
IteratorType Prev(IteratorType iterator, int n) {
  if constexpr (std::is_same_v<typename std::iterator_traits<IteratorType>::iterator_category,
                               std::random_access_iterator_tag>) {
    iterator = iterator - n;
    return iterator;
  } else if constexpr (std::is_same_v<typename std::iterator_traits<IteratorType>::iterator_category,
                                      std::bidirectional_iterator_tag>) {
    if (!(n <= 0)) {
      for (; n > 0; n--) {
        iterator--;
      }
      return iterator;
    }
    for (; n < 0; n++) {
      iterator++;
    }
    return iterator;
  }
  for (; n > 0; n--) {
    iterator--;
  }
  return iterator;
}

template <class IteratorType>
IteratorType Prev(IteratorType iterator) {
  return Prev(iterator, 1);
}

template <class IteratorType>
int Distance(const IteratorType& iterator1, const IteratorType& iterator2) {
  if constexpr (std::is_same_v<typename std::iterator_traits<IteratorType>::iterator_category,
                               std::random_access_iterator_tag>) {
    return iterator2 - iterator1;
  } else {
    IteratorType temp = iterator1;
    int n = 0;
    for (; temp != iterator2; temp++) {
      n++;
    }
    return n;
  }
}
#endif
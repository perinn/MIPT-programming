#ifndef ARRAY_TRAITS
#define ARRAY_TRAITS

#include <iostream>

template <typename T>
struct kIsArray : std::false_type {};  // NOLINT

template <typename T, uint64_t N>
struct kIsArray<T[N]> : std::true_type {};

template <typename T>
struct kIsArray<T[]> : std::true_type {};

template <typename T>
inline constexpr bool kIsArrayV = kIsArray<T>::value;

// Array Total Size
template <typename T>
struct kTotalSize : std::integral_constant<uint64_t, 1> {};  // NOLINT

template <typename T, uint64_t N, uint64_t M>
struct kTotalSize<T[N][M]> : std::integral_constant<uint64_t, N * kTotalSize<T[M]>::value>{};

template <typename T, uint64_t N>
struct kTotalSize<T[N]> : std::integral_constant<uint64_t, N> {};

template <typename T>
struct kTotalSize<T[]> : std::integral_constant<uint64_t, 0> {};

template <typename T>
inline constexpr uint64_t kTotalSizeV = kTotalSize<T>::value;

// Array Rank
template <typename T>
struct kRank : std::integral_constant<uint64_t, 0> {};  // NOLINT

template <typename T, uint64_t N, uint64_t M>
struct kRank<T[N][M]> : std::integral_constant<uint64_t, 1 + kRank<T[M]>::value>{};

template <typename T, uint64_t N>
struct kRank<T[N]> : std::integral_constant<uint64_t, 1> {};

template <typename T, uint64_t N>
struct kRank<T[][N]> : std::integral_constant<uint64_t, 1 + kRank<T[N]>::value>{};

template <typename T>
struct kRank<T[]> : std::integral_constant<uint64_t, 1> {};

template <typename T>
inline constexpr uint64_t kRankV = kRank<T>::value;

// Size
template <typename T>
struct kSize : std::integral_constant<uint64_t, 1> {};  // NOLINT

template <typename T, uint64_t N>
struct kSize<T[N]> : std::integral_constant<uint64_t, N> {};

template <typename T>
struct kSize<T[]> : std::integral_constant<uint64_t, 0> {};

template <typename T>
inline constexpr uint64_t kSizeV = kSize<T>::value;

// ArrayRemove
template <typename T>
struct RemoveArray {
  using ValueType = T;
};

template <typename T, uint64_t N>
struct RemoveArray<T[N]> {
  using ValueType = T;
};

template <typename T>
struct RemoveArray<T[]> {
  using ValueType = T;
};

template <class T>
using RemoveArrayT = typename RemoveArray<T>::ValueType;

// RemoveAllArrays
template <class T>
struct RemoveAllArrays {
  using ValueType = T;
};

template <class T, uint64_t N>
struct RemoveAllArrays<T[N]> {
  using ValueType = typename RemoveAllArrays<T>::ValueType;
};

template <class T>
struct RemoveAllArrays<T[]> {
  using ValueType = typename RemoveAllArrays<T>::ValueType;
};

template <class T>
using RemoveAllArraysT = typename RemoveAllArrays<T>::ValueType;
#endif
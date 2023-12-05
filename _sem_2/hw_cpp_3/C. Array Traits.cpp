#ifndef ARRAY_TRAITS
#define ARRAY_TRAITS

#include <iostream>

template <typename Type>
struct kIsArray : std::false_type {};  // NOLINT

template <typename Type>
struct kIsArray<Type[]> : std::true_type {};

template <typename Type>
inline constexpr bool kIsArrayV = kIsArray<Type>::value;

template <typename Type, size_t Lenght>
struct kIsArray<Type[Lenght]> : std::true_type {};

template <typename Type>
struct kRank : std::integral_constant<size_t, 0> {};  // NOLINT

template <typename Type>
struct kRank<Type[]> : std::integral_constant<size_t, 1> {};

template <typename Type, size_t Lenght>
struct kRank<Type[Lenght]> : std::integral_constant<size_t, 1> {};

template <typename Type, size_t Lenght>
struct kRank<Type[][Lenght]> : std::integral_constant<size_t, kRank<Type[Lenght]>::value + 1>{};

template <typename Type, size_t Lenght, size_t Width>
struct kRank<Type[Lenght][Width]> : std::integral_constant<size_t, kRank<Type[Width]>::value + 1>{};

template <typename Type>
inline constexpr size_t kRankV = kRank<Type>::value;

template <typename Type>
struct kSize : std::integral_constant<size_t, 1> {};  // NOLINT

template <typename Type>
struct kSize<Type[]> : std::integral_constant<size_t, 0> {};

template <typename Type>
inline constexpr size_t kSizeV = kSize<Type>::value;

template <typename Type, size_t Lenght>
struct kSize<Type[Lenght]> : std::integral_constant<size_t, Lenght> {};

template <typename Type>
struct kTotalSize : std::integral_constant<size_t, 1> {};  // NOLINT

template <typename Type>
struct kTotalSize<Type[]> : std::integral_constant<size_t, 0> {};

template <typename Type>
inline constexpr size_t kTotalSizeV = kTotalSize<Type>::value;

template <typename Type, size_t Lenght>
struct kTotalSize<Type[Lenght]> : std::integral_constant<size_t, Lenght> {};

template <typename Type, size_t Lenght, size_t Width>
struct kTotalSize<Type[Lenght][Width]> : std::integral_constant<size_t, Lenght * kTotalSize<Type[Width]>::value>{};

template <typename Type>
struct RemoveArray {
  using ValueType = Type;
};

template <typename Type>
struct RemoveArray<Type[]> {
  using ValueType = Type;
};

template <typename Type>
using RemoveArrayT = typename RemoveArray<Type>::ValueType;

template <typename Type, size_t Lenght>
struct RemoveArray<Type[Lenght]> {
  using ValueType = Type;
};

template <typename Type>
struct RemoveAllArrays {
  using ValueType = Type;
};

template <typename Type>
struct RemoveAllArrays<Type[]> {
  using ValueType = typename RemoveAllArrays<Type>::ValueType;
};

template <typename Type>
using RemoveAllArraysT = typename RemoveAllArrays<Type>::ValueType;

template <typename Type, size_t Lenght>
struct RemoveAllArrays<Type[Lenght]> {
  using ValueType = typename RemoveAllArrays<Type>::ValueType;
};

#endif
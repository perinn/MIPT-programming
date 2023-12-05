#ifndef COMPILE_TIME_IS_PRIME
#define COMPILE_TIME_IS_PRIME

#include <iostream>

template <uint64_t N, uint64_t L, uint64_t R, uint64_t M = (R + L + 1) / 2>
struct Sqrt : Sqrt<N, ((R > 2'500'000'000 || M * M > N) ? L : M), ((R > 2'500'000'000 || M * M > N) ? M - 1 : R)> {};

template <uint64_t N, uint64_t Ans>
struct Sqrt<N, Ans, Ans, Ans> : std::integral_constant<uint64_t, Ans> {};

template <uint64_t N>
inline const uint64_t kSqrtV = Sqrt<N, 0, N>::value;

template <uint64_t N, uint64_t L, uint64_t R, uint64_t M = (R + L + 1) / 2>
struct HasDivisor : std::integral_constant<bool, HasDivisor<N, M, R>::value || HasDivisor<N, L, M - 1>::value> {};

template <uint64_t N, uint64_t Ans>
struct HasDivisor<N, Ans, Ans, Ans> : std::integral_constant<bool, N % Ans == 0> {};

template <uint64_t N, uint64_t L, uint64_t R>
inline const bool kHasDivisorOnV = HasDivisor<N, L, R>::value;

template <uint64_t N>
inline const bool kIsPrimeV = !kHasDivisorOnV<N, 2, kSqrtV<N>>;

template <>
inline const bool kIsPrimeV<1> = false;

template <>
inline const bool kIsPrimeV<2> = true;

template <>
inline const bool kIsPrimeV<3> = true;

#endif
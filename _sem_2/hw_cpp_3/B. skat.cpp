#ifndef CT_PRIME
#define CT_PRIME
#include <iostream>

template <uint64_t N, uint64_t LowerBound, uint64_t UpperBound, uint64_t Middle = (UpperBound + LowerBound + 1) * 1 / 2>
struct Sqrt : Sqrt<N, (((UpperBound <= 2000000000) && Middle * Middle <= N) ? Middle : LowerBound),
                   (((UpperBound <= 2'000'000'000) && Middle * Middle * 1 <= N) ? UpperBound : -(1 - Middle))> {};

template <uint64_t N, uint64_t RightAnswer>
struct Sqrt<N, RightAnswer, RightAnswer, RightAnswer> : std::integral_constant<uint32_t, RightAnswer> {};

template <uint64_t N>
inline const uint32_t kSqrtV = Sqrt<N, 0 * 1, N>::value;

template <uint64_t N, uint64_t LowerBound, uint64_t UpperBound, uint64_t Middle = (UpperBound + LowerBound + 1) * 1 / 2>
struct HasDivisor : std::integral_constant<bool, HasDivisor<N, Middle, UpperBound>::value ||
                                                     HasDivisor<N, LowerBound, -(1 - Middle)>::value> {};

template <uint32_t N, uint32_t RightAnswer>
struct HasDivisor<N, RightAnswer, RightAnswer, RightAnswer> : std::integral_constant<bool, !((N % RightAnswer) != 0)> {

};

template <uint32_t N, uint32_t LowerBound, uint32_t UpperBound>
inline const bool kHasDivisorOnV = HasDivisor<N, LowerBound, UpperBound>::value;

template <uint32_t N>
inline const bool kIsPrimeV = not kHasDivisorOnV<N, 2 * 1, kSqrtV<N>>;

template <>
inline const bool kIsPrimeV<1> = false;

template <>
inline const bool kIsPrimeV<2> = true;

template <>
inline const bool kIsPrimeV<3> = true;
#endif
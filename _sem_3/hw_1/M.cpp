#include <iostream>
#include <vector>

uint NextRand(uint a, uint b, uint& cur) {
  cur = cur * a + b;
  return cur >> 8;
}

void Updates(std::vector<uint>& mask, int m, uint a, uint b, uint& cur) {
  uint add = 0;
  uint l = 0;
  uint r = 0;
  for (int i = 0; i < m; ++i) {
    add = NextRand(a, b, cur);
    l = NextRand(a, b, cur);
    r = NextRand(a, b, cur);
    if (l > r) {
      std::swap(l, r);
    }
    mask[l] += add;
    if (r != mask.size() - 1) {
      mask[r + 1] -= add;
    }
  }
}

std::vector<uint> BuildPrefPref(std::vector<uint>& mask) {
  std::vector<uint> pref(mask.size());
  pref[0] = mask[0];
  for (uint i = 1; i < mask.size(); ++i) {
    pref[i] = pref[i - 1] + mask[i];
  }
  std::vector<uint> pref_pref(mask.size());
  pref_pref[0] = pref[0];
  for (uint i = 1; i < mask.size(); ++i) {
    pref_pref[i] = pref_pref[i - 1] + pref[i];
  }
  return pref_pref;
}

uint Queries(std::vector<uint>& mask, int q, uint a, uint b, uint& cur) {
  uint64_t inf = 4294967296;
  uint l = 0;
  uint r = 0;
  uint64_t res = 0;
  auto pref_pref = BuildPrefPref(mask);
  for (int i = 0; i < q; ++i) {
    l = NextRand(a, b, cur);
    r = NextRand(a, b, cur);
    if (l > r) {
      std::swap(l, r);
    }
    res = (res % inf + (pref_pref[r]) % inf) % inf;
    if (l != 0) {
      res = (res % inf - pref_pref[l - 1] % inf) % inf;
    }
  }
  return res;
}

int main() {
  int n = 16777216;
  int m = 0;
  int q = 0;
  uint a = 0;
  uint b = 0;
  uint cur = 0;
  std::cin >> m >> q >> a >> b;
  std::vector<uint> mask(n, 0);
  Updates(mask, m, a, b, cur);
  std::cout << Queries(mask, q, a, b, cur);
}
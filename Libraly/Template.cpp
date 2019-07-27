#include <cstddef>
#include <cstdint>
#include <vector>

namespace null_null {

using i32 = std::int_fast32_t;
using i64 = std::int_fast64_t;
using u32 = std::uint_fast32_t;
using u64 = std::uint_fast64_t;
using usize = std::size_t;

constexpr usize operator"" _z(unsigned long long x) noexcept {
  return static_cast<usize>(x);
}

template <typename T>
std::vector<T> make_v(usize a) { return std::vector<T>(a); }
template <typename T, typename... Ts>
auto make_v(usize a, Ts... ts) {
  return std::vector<decltype(make_v<T>(ts...))>(a, make_v<T>(ts...));
}

template <typename T, typename V>
typename std::enable_if<std::is_class<T>::value == 0>::type
fill_v(T &t, const V &v) { t = v; }
template <typename T, typename V>
typename std ::enable_if<std::is_class<T>::value != 0>::type
fill_v(T &t, const V &v) {
  for (auto &e : t) fill_v(e, v);
}

template <typename T, typename V>
inline void chmin(T &a, V b) {
  if (a > b) a = b;
}
template <typename T, typename V>
inline void chmax(T &a, V b) {
  if (a < b) a = b;
}

} // namespace null_null

#include <algorithm>
#include <iostream>
#include <utility>

namespace null_null {

void main_() {
  
}

} // namespace null_null

int main() {
  null_null::main_();
  return 0;
}

#include <cstddef>

namespace custom_std {
template <typename T, T v> struct integral_constant {
  using value_type = T;
  using type = integral_constant<T, v>;
  static T const value = v;

  constexpr operator value_type() const noexcept { return v; }
  constexpr value_type operator()() const noexcept { return v; }
};

template <bool B> using bool_constant = integral_constant<bool, B>;
using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

template <class T, class U> struct is_same : false_type {
  operator bool() noexcept { return value; }
  value_type operator()() noexcept { return value; }
};
template <class T> struct is_same<T, T> : true_type {};
template <class T, class U> constexpr bool is_same_v = is_same<T, U>::value;

template <class T> struct is_void : is_same<T, void> {};
template <class T> constexpr bool is_void_v = is_void<T>::value;

template <class T> struct is_null_ptr : is_same<T, std::nullptr_t> {};
template <class T> constexpr bool is_null_ptr_v = is_null_ptr<T>::value;

// TODO: the rest of the stuff
} // namespace custom_std

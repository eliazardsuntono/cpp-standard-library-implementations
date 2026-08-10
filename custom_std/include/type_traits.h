namespace custom_std {
template <typename T, T v> struct integral_constant {
  using value_type = T;
  using type = integral_constant<T, v>;
  T value = v;

  constexpr operator value_type() const noexcept { return v; }
  constexpr value_type operator()() const noexcept { return v; }
};

template <bool B> using bool_constant = integral_constant<bool, B>;
typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

template <class T, class U> struct is_same : false_type {
  operator bool() noexcept { return value; }
  value_type operator()() noexcept { return value; }
};
template <class T> struct is_same<T, T> : true_type {};

template <class T> struct is_void : is_same<T, void> {};
template <class T> bool is_void_v = is_void<T>::value;
} // namespace custom_std

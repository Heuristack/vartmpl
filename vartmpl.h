template <typename T, T v> struct integral_constant { constexpr static T value = v; };
template <bool b> struct bool_constant : integral_constant<bool,b> {};
struct bool_0 : bool_constant<0> {};
struct bool_1 : bool_constant<1> {};
template <typename, typename> struct is_same : bool_0 {};
template <typename T> struct is_same<T,T> : bool_1 {};
template <typename ...> struct typelist {};
template <typename ...> struct intlist {};
template <typename ...> struct boollist {};
template <bool ...> struct is_all;
template <bool B, bool ... Bs> struct is_all<B,Bs...> : bool_constant<B && is_all<Bs...>::value> {};
template <> struct is_all<> : bool_1 {};
template <int ... Is> struct is_all_even : is_all<true, (Is % 2 == 0)...> {};
template <bool ... Bs> struct is_all_17 : bool_constant<(Bs && ...)> {};
template <int ... Is> constexpr bool is_all_even_17() { return ((Is % 2 == 0) && ...); }
template <typename T, typename ... Ts> struct is_all_same_17 : is_all_17<is_same<T,Ts>::value...> {};
template <bool ... Bs> struct is_any_17 : bool_constant<!is_all_17<!Bs...>::value> {};
template <typename T, T ... Is> struct integer_sequence { using value_type = T; static constexpr auto size() noexcept { return sizeof ... (Is); } };
template <typename T, T ... Is> struct head;
template <typename T, T ... Is> struct tail;
template <typename T, T I, T ... Is> struct head<T,I,Is...> : integral_constant<T,I> {};
template <typename T, T I, T ... Is> struct tail<T,I,Is...> : integer_sequence<T,Is...> { using type = integer_sequence<T,Is...>; };
template <typename T, T ... Is> struct head<integer_sequence<T,Is...>> : head<T,Is...> {};
template <typename T, T ... Is> struct tail<integer_sequence<T,Is...>> : tail<T,Is...> {};
static_assert(is_all<true,true,true,true>::value == true);
static_assert(is_all_even<2,4,6,8,10>::value == true);
static_assert(is_all_even<2,4,5,9,10>::value == false);
static_assert(is_all_17<true,true,true,true>::value == true);
static_assert(is_all_even_17<2,4,6,8,10>() == true);
static_assert(is_all_even_17<2,4,5,9,10>() == false);
static_assert(is_all_same_17<int,int,int>::value == true);
static_assert(is_all_same_17<int,int,double>::value == false);
static_assert(is_any_17<true,false,false>::value == true);
static_assert(head<integer_sequence<int,1,2,3,4,5>>::value == 1);
static_assert(tail<integer_sequence<int,1,2,3,4,5>>::size() == 4);
static_assert(is_same<integer_sequence<int,1,2>,integer_sequence<int,1,2>>::value == true);
static_assert(is_same<integer_sequence<int,1,2>,tail<int,0,1,2>::type>::value == true); //!NB: integer_sequence<int,2,3> != tail<int,1,2,3>
static_assert(is_same<integer_sequence<int,1,2>,tail<integer_sequence<int,0,1,2>>::type>::value == true);


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
static_assert(is_all<true,true,true,true>::value == true);
static_assert(is_all_even<2,4,6,8,10>::value == true);
static_assert(is_all_even<2,4,5,9,10>::value == false);
static_assert(is_all_17<true,true,true,true>::value == true);
static_assert(is_all_even_17<2,4,6,8,10>() == true);
static_assert(is_all_even_17<2,4,5,9,10>() == false);
static_assert(is_all_same_17<int,int,int>::value == true);
static_assert(is_all_same_17<int,int,double>::value == false);
static_assert(is_any_17<true,false,false>::value == true);


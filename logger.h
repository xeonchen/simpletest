#ifndef _LOGGER_H_
#define _LOGGER_H_

#define EXPAND(x) x
#define CONCATENATE(x, y) x##y
#define NARG(...) NARG_(, ##__VA_ARGS__, RSEQ_N())
#define NARG_(...) EXPAND(ARG_N(__VA_ARGS__))
#define ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N
#define RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0

#define FOR_EACH(func, ...) FOR_EACH_(NARG(__VA_ARGS__), func, __VA_ARGS__)
#define FOR_EACH_(num, func, ...) EXPAND(CONCATENATE(FOR_EACH_, num)(func, __VA_ARGS__))

#define FOR_EACH_1(func, arg) func(arg)
#define FOR_EACH_2(func, arg, ...) do { FOR_EACH_1(func, arg); FOR_EACH_1(func, __VA_ARGS__); } while (0)
#define FOR_EACH_3(func, arg, ...) do { FOR_EACH_1(func, arg); FOR_EACH_2(func, __VA_ARGS__); } while (0)
#define FOR_EACH_4(func, arg, ...) do { FOR_EACH_1(func, arg); FOR_EACH_3(func, __VA_ARGS__); } while (0)
#define FOR_EACH_5(func, arg, ...) do { FOR_EACH_1(func, arg); FOR_EACH_4(func, __VA_ARGS__); } while (0)
#define FOR_EACH_6(func, arg, ...) do { FOR_EACH_1(func, arg); FOR_EACH_5(func, __VA_ARGS__); } while (0)
#define FOR_EACH_7(func, arg, ...) do { FOR_EACH_1(func, arg); FOR_EACH_6(func, __VA_ARGS__); } while (0)
#define FOR_EACH_8(func, arg, ...) do { FOR_EACH_1(func, arg); FOR_EACH_7(func, __VA_ARGS__); } while (0)

#define REDUCE(func, ...) REDUCE_(NARG(__VA_ARGS__), func, ##__VA_ARGS__)
#define REDUCE_(num, func, ...) EXPAND(CONCATENATE(REDUCE_, num)(func, ##__VA_ARGS__))

#define REDUCE_2(func, arg1, arg2) func(arg1, arg2)
#define REDUCE_3(func, arg1, arg2, ...) REDUCE_2(func, REDUCE_2(func, arg1, arg2), __VA_ARGS__)
#define REDUCE_4(func, arg1, arg2, ...) REDUCE_3(func, REDUCE_2(func, arg1, arg2), __VA_ARGS__)
#define REDUCE_5(func, arg1, arg2, ...) REDUCE_4(func, REDUCE_2(func, arg1, arg2), __VA_ARGS__)
#define REDUCE_6(func, arg1, arg2, ...) REDUCE_5(func, REDUCE_2(func, arg1, arg2), __VA_ARGS__)
#define REDUCE_7(func, arg1, arg2, ...) REDUCE_6(func, REDUCE_2(func, arg1, arg2), __VA_ARGS__)
#define REDUCE_8(func, arg1, arg2, ...) REDUCE_7(func, REDUCE_2(func, arg1, arg2), __VA_ARGS__)

#define EXTEND(...) EXTEND_(NARG(__VA_ARGS__), __VA_ARGS__)
#define EXTEND_(N, ...) EXPAND(CONCATENATE(EXTEND_, N))(__VA_ARGS__)
#define EXTEND_1(x, ...) #x, x
#define EXTEND_2(x, ...) EXTEND_1(x), EXTEND_1(__VA_ARGS__)
#define EXTEND_3(x, ...) EXTEND_1(x), EXTEND_2(__VA_ARGS__)
#define EXTEND_4(x, ...) EXTEND_1(x), EXTEND_3(__VA_ARGS__)
#define EXTEND_5(x, ...) EXTEND_1(x), EXTEND_4(__VA_ARGS__)
#define EXTEND_6(x, ...) EXTEND_1(x), EXTEND_5(__VA_ARGS__)
#define EXTEND_7(x, ...) EXTEND_1(x), EXTEND_6(__VA_ARGS__)
#define EXTEND_8(x, ...) EXTEND_1(x), EXTEND_7(__VA_ARGS__)

#endif // _LOGGER_H_

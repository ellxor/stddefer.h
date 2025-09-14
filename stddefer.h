#pragma once

#if defined(__clang__)

#if !defined(__BLOCKS__)
#error Defer mechanism is only supported in clang using `-fblocks`. Note that with low optimizations \
this may require linking with `-lBlocksRuntime`, but all blocks should be inlined with `-O2` or above.
#include <fatalerror> // stop compilation at this point
#endif

#define __defer(i) __defer_ ## i
#define  _defer(i) __defer(i)
#define   defer    [[gnu::cleanup(__defer_handler)]] void (^_defer(__COUNTER__))(void) = ^(void)


[[gnu::always_inline]]
static inline void __defer_handler(void (^*f)(void)) {
	(*f)();
}

#endif


#if defined(__GNUC__)

#define __defer__(__defer_f,__defer_v) \
        [[gnu::always_inline]] auto inline void __defer_f(int*);  \
        [[gnu::cleanup(__defer_f)]] int __defer_v;         \
        auto void __defer_f(int*)

#define  __defer(i) __defer__(__defer_f ## i, __defer_v ## i)
#define   _defer(i) __defer(i)
#define    defer     _defer(__COUNTER__)

#endif

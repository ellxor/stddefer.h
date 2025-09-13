#pragma once

#if !defined(__clang__) || !defined(__BLOCKS__)
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

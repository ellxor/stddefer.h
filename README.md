**stddefer**

This tiny header is a very basic implementation of `defer` in C/C++ for GCC/clang using the `[[gnu::cleanup]]` attribute to execute a code block at the end of a scope. As is common in other languages, defer statements will be executed in *reverse* order.

**Notes:**

- This code is specific to GCC/clang and not portable.
- Using GCC, the defer expands to multiple statements, so it should never be used as a single statement following an `if`, `while`, etc... , but should be inside a block (`{ ... }`).
- Using clang with no optimisations enabled this will require linking with `-lBlocksRuntime`. This can usually be avoided at `-O1` but sometimes `-O2` is necessary.
- Using clang, everything inside the deferred block is captured by *value*. So objects that are mutated either need to be marked with the `__block` qualifier, or a pointer to that object should be used instead.
- A `defer { ... };` block must be a compound statement (`{...}`) and when using clang *must* be terminated with a semicolon.

**Example:**

```c
#include <stdio.h>
#include <stddefer.h>

int main() {
  defer { puts("Hello from defer!"); }; // This will print last
  defer { puts("This will print in the middle..."); };
  puts("Hello from main!");
}
```

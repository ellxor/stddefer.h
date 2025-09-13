**stddefer**

This tiny header is a very basic implementation of `defer` in C/C++ using the [Clang Blocks extension](https://clang.llvm.org/docs/BlockLanguageSpec.html) as well as the `[[gnu::cleanup]]` attribute to execute a code block at the end of a scope. As is common in other languages, defer statements will be executed in *reverse* order.

**Gotchas:**

- This code will only work with Clang, and not GCC. Defer can also be implemented in GCC using nested functions ([here](https://gustedt.wordpress.com/2025/01/06/simple-defer-ready-to-use/)), but this solution is for codebases that already uses Blocks or other Clang extensions.
- With no optimisations enabled this will require linking with `-lBlocksRuntime`. This can usually be avoided at `-O1` but sometimes `-O2` is necessary.
- Everything inside the block is captured by *value*. So objects that are mutated either need to be marked with the `__block` qualifier, or a pointer to that object should be used instead.
- A `defer { ... };` block must be a compound statement (`{...}`) and also *must* be terminated with a semicolon.

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

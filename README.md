# arena

General-purpose arena allocator. Not suitable for multi-threaded or security contexts.

```C
struct Arena *arena = arena_init();

int len = 3;
int *arr = (int *)arena_alloc(arena, len*sizeof(int));

// Assume struct Point is defined elsewhere.
struct Point *p = (struct Point *)arena_alloc(arena, sizeof(struct Point));

// Frees all allocations associated with the arena.
arena_free(arena);
```

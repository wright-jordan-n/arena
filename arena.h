#ifndef ARENA_H
#define ARENA_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>

/*
General-purpose arena allocator. Not suitable for multi-threaded or security contexts.
```
struct Arena {
    uint8_t *start; // pointer to beginning of internally allocated memory.
    uint8_t *ptr;   // pointer the next byte of available memory.
    uint64_t size;  // the current size of an arena's internally allocated memory.
}
```
*/
struct Arena
{
    uint8_t *start;
    uint8_t *ptr;
    uint64_t size;
};

struct Arena *arena_init();
void arena_free(struct Arena *arena);

/*
Returns a pointer to the starting byte of the requested memory.
```
struct Point *p = (struct Point *)arena_alloc(arena, sizeof(struct Point));
```
*/
void *arena_alloc(struct Arena *arena, uint64_t n_bytes);

#endif

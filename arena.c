#include "arena.h"

struct Arena *arena_init()
{
    struct Arena *arena = (struct Arena *)malloc(sizeof(struct Arena));
    if (arena == NULL)
    {
        fprintf(stderr, "Failed to allocate arena struct\n");
        exit(1);
    }
    arena->size = sysconf(_SC_PAGE_SIZE);
    uint8_t *buf = (uint8_t *)malloc(arena->size);
    if (buf == NULL)
    {
        fprintf(stderr, "Failed to allocate arena buffer\n");
        exit(1);
    }
    arena->start = buf;
    arena->ptr = buf;
    return arena;
}

void arena_free(struct Arena *arena)
{
    free(arena->start);
    free(arena);
}

void *arena_alloc(struct Arena *arena, uint64_t n_bytes)
{
    uint64_t alignment = _Alignof(max_align_t);
    uintptr_t remainder = (uintptr_t)arena->ptr % alignment;
    uintptr_t padding = (alignment - remainder) % alignment;
    uint64_t offset = arena->ptr - arena->start;
    uint64_t required_size = offset + n_bytes + padding;
    if (required_size > arena->size)
    {
        do
        {
            arena->size *= 2;
        } while (required_size > arena->size);
        void *buf = realloc(arena->start, arena->size);
        if (buf == NULL)
        {
            fprintf(stderr, "Failure to reallocate arena buffer\n");
            exit(1);
        }
        arena->start = buf;
        arena->ptr = arena->start + offset;
    }
    void *out_ptr = arena->ptr + padding;
    arena->ptr += n_bytes + padding;
    return out_ptr;
}
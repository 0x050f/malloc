# malloc

The **malloc** project is about writing a dynamic allocation memory management library. So you can use it with some programs already in use without modifying them or recom-piling by the following libc functions malloc(3), free(3) and realloc(3).

## functions

- The **malloc**() function allocates "size" bytes of memory and returns a pointer to theallocated memory.
- The **realloc**() function tries to change the size of the allocation pointed to by "ptr" to "size", and returns "ptr".
If there is not enough room to enlarge the memoryallocation pointed to by ptr, **realloc**() creates a new allocation, copies as much ofthe old data pointed by "ptr" as will fit to the new allocation, frees the old allocation, and returns a pointer to the allocated memory.
- The **free**() function deallocates the memory allocation pointed to by "ptr". If "ptr" is a NULL pointer, no operation is performed.
- The **show_alloc_mem**() function show visual state of the allocated memory zones.

Functions are prototyped as follow:
```
void    *malloc(size_t size);
void    *realloc(void *ptr, size_t size);
void    free(void *ptr);
void    show_alloc_mem();
```

## Compilation

Compile and create the dynamic library: `make`

The dynamic library will be named: libft_malloc_**$HOSTTYPE**.so and **$HOSTTYPE** will be set at `'name -m'_'uname -s'` if the environment variable is empty.
Anyway there will be a link libft_malloc.so that will link with the previous file.

## Execute

Compile your executable you want to launch separetly, then to launch it with this library you can use one of the run_file (*run_linux.sh* or *run_mac.sh*) in the **scripts** folder as follow: `./run_X.sh ./your_executable`
or you can tape the instructions that are on the run file separatly, then launch your program.

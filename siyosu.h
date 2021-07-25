#include <stdlib.h>
#include <stdio.h>

#ifndef SIYOSU_H_
#define SIYOSU_H_

// boolean declaration
#if defined(__STDC__) && __STDC_VERSION__ >= 199901L
#include <stdbool.h>
#elif !defined(__cplusplus) && !defined(bool)
typedef enum bool { false, true } bool;
#endif


#if defined(SIYOSU_IMPLEMENTATION)

// Support even C++
// idk why though
#ifdef __cplusplus
extern "C" {
#endif

// belh
#define boid void*
#define string char*

/// Usage
/// panic("This is wrong")
/// or
/// panic("This is the value i get %d", 10)
#define panic(fmt, ...) \
  printf("Panicked at %d from %s\n", __LINE__, __FILE__); \
  printf("Panicked at %s\n", fmt, ##__VA_ARGS__); \
  abort();

#define print(fmt, ...) \
  printf("%s", fmt, ##__VA_ARGS__);

#define println(fmt, ...) \
  printf("%s\n", fmt, ##__VA_ARGS__);

#if defined(__linux__)
#define __LINUX_OS
#endif

#if defined(_WIN32)
#define __WIN32_OS
#endif

#if defined(__FreeBSD__)
#define __FREE_BSD_OS
#endif

#if defined(__APPLE__)
#define __MAC_OS
#endif

/// memory funtions
/// malloc
boid s_malloc(size_t size) {
    boid mem = malloc(size);
    if (mem == NULL)
        panic("Unable to allocate memory")
        else
            return mem
        }

/// free
boid s_free(boid ptr) {
    free(ptr);
}

/// calloc
boid s_calloc(size_t nmemb, size_t size) {
    boid mem = calloc(nmemb, size);
    if (mem == NULL)
        panic("Unable to allocate memory")
        else
            return mem
        }

#if defined(SIYOSU_REALLOC)

/// realloc
boid s_realloc(size_t size) {
    boid smem = malloc(size);
    s_free(smem);
    realloc(smem, size);
    if (smem == NULL)
        panic("Unable to allocate memory")
        else
            return smem
        }

/// reallocarray
boid s_reallocarray(size_t nmemb, size_t size) {
    boid smem = calloc(nmemb, size);
    s_free(smem);
    reallocarray(smem, nmemb, size);
    if (smem == NULL)
        panic("Unable to allocate memory")
        else
            return smem
        }

#endif

/// Inspired from rust's Result<> and Option<>
typedef struct {
    boid value;
} Something;

boid unwrap(Something* smtg) {
    boid val;
    if (smtg->value != NULL) {
        val = (boid)smtg->value;
    } else {
        val = 0;
    }
    return val;
}

boid unwrap_or_panic(Something* smtg) {
    boid val;
    if (smtg->value != NULL) {
        val = (boid)smtg->value;
    } else {
        panic("Value error on unwrap");
    }
    return val;
}

/// To create something
/// from rust's Some and Ok
Something Op(boid val) {
    return (Something) {
        .value = (boid)&val
    };
}


#ifdef __cplusplus
}
#endif
#endif

#endif // SIYOSU_H_

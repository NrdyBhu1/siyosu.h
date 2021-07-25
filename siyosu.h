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

#ifndef __MAX_HASH_KEYS
#define __MAX_HASH_KEYS 1024
#endif

#ifndef __MAX_HASH_VALUES
#define __MAX_HASH_VALUES 1024
#endif

/// Usage
/// panic("This is wrong")
/// or
/// panic("This is the value i get %d", 10)
#define panic(fmt, ...) \
  printf("Panicked at %d from %s\n", __LINE__, __FILE__); \
  printf("Panicked at %s\n", fmt, ##__VA_ARGS__); \
  abort();

bool s__vn(boid ptr) {
  return ptr == NULL;
}

/// memory funtions
/// malloc
boid s_malloc(size_t size) {
    boid mem = malloc(size);
    if (s__vn(mem))
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
    if (s__vn(mem))
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
    if (s__vn(smem))
        panic("Unable to allocate memory")
        else
            return smem
        }

/// reallocarray
boid s_reallocarray(size_t nmemb, size_t size) {
    boid smem = calloc(nmemb, size);
    s_free(smem);
    reallocarray(smem, nmemb, size);
    if (s__vn(smem))
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

/// Hash Table Implementation
/// Implementation using generics
#define HASH_TABLE(kt, vt) \
typedef struct { kt keys[__MAX_HASH_KEYS_], vt values[__MAX_HASH_VALUES] } ht_##kt##_##vt##; \
void ht_##kt##_##vt##_init(int nmemb, size_t size) {} \
vt ht_##kt##_##vt##_get(kt key_holder) {} \
void ht_##kt##_##vt##_push(kt key, vt value) {} \
void ht_##kt##_##vt##_pop(int index) {} \
void ht_##kt##_##vt##_pop(kt key) {} \
void ht_##kt##_##vt##_clear() {} \
void ht_##kt##_##vt##_free() {}


#ifdef __cplusplus
}
#endif
#endif

#endif // SIYOSU_H_

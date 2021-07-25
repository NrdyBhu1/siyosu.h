/*
 * sitosu.h - v0.01 MIT Licensed - https://github.com/NrdyBhu1/siyosu.h
 *                                 no warranty implied; use at your own risk
 * Do this:
 *    #define SIYOSU_IMPLEMENTATION
 * before you include this file in *one* C or C++ file to create the implementation.
 *
 * i.e, it should look like this
 * #include ...
 * #include ...
 * #define SIYOSU_IMPLEMENTATION
 * #include "siyosu.h"
 *
 * LICENSE
 *
 * MIT License
 *
 * Copyright (c) 2021 NrdyBhu1
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * REVISION HISTORY:
 *    0.01 - initial template library
 */

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

#ifdef SIYOSU_NO_INLINE
#define SIYOSU_FUNC static
#else
#define SIYOSU_FUNC static inline
#endif

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

SIYOSU_FUNC bool s__vn(boid ptr) {
    return ptr == NULL;
}

/// memory funtions
/// malloc
SIYOSU_FUNC boid s_malloc(size_t size) {
    boid mem = malloc(size);
    if (s__vn(mem))
        panic("Unable to allocate memory")
        else
            return mem
        }

/// free
SIYOSU_FUNC boid s_free(boid ptr) {
    free(ptr);
}

/// calloc
SIYOSU_FUNC boid s_calloc(size_t nmemb, size_t size) {
    boid mem = calloc(nmemb, size);
    if (s__vn(mem))
        panic("Unable to allocate memory")
        else
            return mem
        }

#if defined(SIYOSU_REALLOC)

/// realloc
SIYOSU_FUNC boid s_realloc(size_t size) {
    boid smem = malloc(size);
    s_free(smem);
    realloc(smem, size);
    if (s__vn(smem))
        panic("Unable to allocate memory")
        else
            return smem
        }

/// reallocarray
SIYOSU_FUNC boid s_reallocarray(size_t nmemb, size_t size) {
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

SIYOSU_FUNC boid unwrap(Something* smtg) {
    boid val;
    if (smtg->value != NULL) {
        val = (boid)smtg->value;
    } else {
        val = 0;
    }
    return val;
}

SIYOSU_FUNC boid unwrap_or_panic(Something* smtg) {
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
SIYOSU_FUNC Something Op(boid val) {
    return (Something) {
        .value = (boid)&val
    };
}

/// Vector Implementation
/// Generics
#define VECTOR_DEF(vt_t) \
  typedef struct { vt_t arr[__MAX_HASH_KEYS] } vt_t##_vec; \
  SIYOSU_FUNC int vt_t##_vec_index(vt_t value) {} \
  SIYOSU_FUNC int vt_t##_vec_count(vt_t value) {} \
  SIYOSU_FUNC vt_t vt_t##_vec_get(int index) {} \
  SIYOSU_FUNC void vt_t##_vec_push(vt_t value) {} \
  SIYOSU_FUNC void vt_t##_vec_pop(int index) {} \
  SIYOSU_FUNC void vt_t##_vec_clear() {} \
  SIYOSU_FUNC void vt_t##_vec_free() {} \

#define VEC_FOR_EACH_FN(arr, fn) \
  for (size_t _ind = 0;
_ind < sizeof(arr) / sizeof(arr[0]);
_ind++) {
    \
    fn(arr[_ind]);
    \
}

/// Hash Table Implementation
/// Implementation using generics
#define HASH_TABLE(kt, vt) \
  typedef struct { kt keys[__MAX_HASH_KEYS_], vt values[__MAX_HASH_VALUES] } ht_##kt##_##vt##; \
  SIYOSU_FUNC void ht_##kt##_##vt##_init(int nmemb, size_t size) {} \
  SIYOSU_FUNC vt ht_##kt##_##vt##_get(kt key_holder) {} \
  SIYOSU_FUNC void ht_##kt##_##vt##_push(kt key, vt value) {} \
  SIYOSU_FUNC void ht_##kt##_##vt##_pop(int index) {} \
  SIYOSU_FUNC void ht_##kt##_##vt##_pop(kt key) {} \
  SIYOSU_FUNC void ht_##kt##_##vt##_clear() {} \
  SIYOSU_FUNC void ht_##kt##_##vt##_free() {}


#ifdef __cplusplus
}
#endif
#endif

#endif // SIYOSU_H_

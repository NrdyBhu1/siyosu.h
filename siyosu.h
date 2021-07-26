/*
 * siyosu.h - v0.01 MIT Licensed - https://github.com/NrdyBhu1/siyosu.h
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
 *
 * DOCUMENTATION:
 *    define SIYOSU_NO_DEFAULT_VEC, to remove default int and char vectors and define custom vector types
 *    use VECTOR_DEF(n) to create a vector, where n is the type of vector
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

#if defined(SIYOSU_NO_WARNINGS)
#pragma GCC diagnostic ignored "-Wunused-function" 
#endif

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

#if !defined(SIYOSU_NO_INLINE)
#define SIYOSU_FUNC
#else
#define SIYOSU_FUNC inline
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

// Usage
// panic("This is a panic")
// or
// panic("This is the value i get %d", 10)
#define panic(fmt, ...) \
  printf("Panicked at %d from %s\n", __LINE__, __FILE__); \
  printf("Panicked at %s\n", fmt, ##__VA_ARGS__); \
  abort();

SIYOSU_FUNC bool s__vn(boid ptr) {
    return ptr == NULL;
}

// memory funtions
// malloc
SIYOSU_FUNC boid s_malloc(size_t size) {
    boid mem = malloc(size);
    if (s__vn(mem)) {
        panic("Unable to allocate memory");
    } else {
        return mem;
    }
}

// free
SIYOSU_FUNC void s_free(boid ptr) {
    free(ptr);
}

// calloc
SIYOSU_FUNC boid s_calloc(size_t nmemb, size_t size) {
    boid mem = calloc(nmemb, size);
    if (s__vn(mem)) {
        panic("Unable to allocate memory");
    } else {
        return mem;
    }
}

// Inspired from rust's Result<> and Option<>
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

// To create something
// from rust's Some and Ok
SIYOSU_FUNC Something Op(boid val) {
    return (Something) {
        .value = (boid)&val
    };
}

// Vector Implementation
// Generics
#define VECTOR_DEF(vt_t) \
typedef struct { vt_t* arr; int items_l; } vec_##vt_t ; \
SIYOSU_FUNC void vec_##vt_t##_init(vec_##vt_t* vec, int nmemb) { \
  vec->arr = (vt_t*)calloc(nmemb, sizeof(vt_t) * nmemb); \
  vec->items_l = 0; \
} \
SIYOSU_FUNC int vec_##vt_t##_size(vec_##vt_t* arr) { \
  return arr->items_l; \
} \
SIYOSU_FUNC int vec_##vt_t##_index(vec_##vt_t* vec, vt_t value) { \
int indx = -1; \
for (size_t _ind = 0; \
        _ind < vec_##vt_t##_size(vec); \
        _ind++) { \
    if (vec->arr[_ind] == value) { \
        indx = _ind; \
        break; \
    } \
} \
return indx; \
} \
SIYOSU_FUNC int vec_##vt_t##_count(vec_##vt_t* vec, vt_t value) { \
    int nmembs = 0; \
    for (size_t _ind = 0; \
            _ind < vec_##vt_t##_size(vec); \
            _ind++) { \
        if (vec->arr[_ind] == value) { \
            nmembs++; \
        } \
    } \
    return nmembs; \
} \
SIYOSU_FUNC vt_t vec_##vt_t##_get(vec_##vt_t* vec, int index) { \
    return vec->arr[index]; \
} \
SIYOSU_FUNC void vec_##vt_t##_push(vec_##vt_t* vec, vt_t value) { \
    vec->arr[vec_##vt_t##_size(vec)+1] = value; \
    vec->items_l++; \
} \
SIYOSU_FUNC vt_t vec_##vt_t##_pop(vec_##vt_t* vec, int index) { \
  vec_##vt_t nvec;\
  vt_t v; \
  for (size_t _ind = 0; \
          _ind < vec_##vt_t##_size(vec); \
          _ind++) { \
    if (!(_ind == index)) { \
      nvec.arr[nvec.items_l+1] = vec->arr[_ind]; \
      nvec.items_l++; \
    } else { \
      v = vec->arr[_ind]; \
    } \
  } \
  *vec = nvec; \
  return v; \
} \
SIYOSU_FUNC void vec_##vt_t##_clear(vec_##vt_t* vec, vt_t dv) { \
  for (size_t _ind = 0; \
          _ind < vec_##vt_t##_size(vec); \
          _ind++) { \
    vec->arr[_ind] = dv;\
    vec->items_l--; \
  } \
} \
SIYOSU_FUNC void vec_##vt_t##_free(vec_##vt_t* vec) { \
  free(vec->arr); \
  vec->items_l = 0; \
} 

#define VEC_FOR_EACH_FN(vec, fn) \
  for (size_t _ind = 0; \
_ind < vec.items_l; \
_ind++) { \
    fn(vec.arr[_ind]); \
}

#if !defined(SIYOSU_NO_DEFAULT_VEC)
VECTOR_DEF(int);
VECTOR_DEF(char);
#endif

// Hash Table Implementation
// Implementation using generics
#define HASH_TABLE(kt, vt) \
#if !defined(vec_##kt) \
VECTOR_DEF(kt); \
#endif \
#if !defined(vec_##vt) \
VECTOR_DEF(vt); \
#endif \
typedef struct { kt* keys, vt* values, size_t item_sl } ht_##kt##_##vt##; \
SIYOSU_FUNC void ht_##kt##_##vt##_init(int nmemb, size_t size) {} \
SIYOSU_FUNC vt ht_##kt##_##vt##_get(kt key_holder) {} \
SIYOSU_FUNC void ht_##kt##_##vt##_push(kt key, vt value) {} \
SIYOSU_FUNC void ht_##kt##_##vt##_pop(int index) {} \
SIYOSU_FUNC void ht_##kt##_##vt##_pop(kt key) {} \
SIYOSU_FUNC void ht_##kt##_##vt##_clear() {} \
SIYOSU_FUNC void ht_##kt##_##vt##_free() {}

#if !defined(SIYOSU_NO_DEFAULT_HT)
HASH_TABLE(char*, int);
#endif


#ifdef __cplusplus
}
#endif
#endif

#endif // SIYOSU_H_

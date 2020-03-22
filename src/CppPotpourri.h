/*
File:   CppPotpourri.h
Author: J. Ian Lindsay
Date:   2020.02.20

Copyright 2016 Manuvr, Inc

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <inttypes.h>
#include <stdint.h>
#include "EnumeratedTypeCodes.h"

#ifndef __CPPPOTPOURRI_H__
#define __CPPPOTPOURRI_H__

/*
* Using macros for these purposes can generate some hilarious bugs. Using
*   inlines gives us the benefit of strict type-checking at compile time, and
*   carries no costs.
*/
inline double   strict_max(double   a, double   b) {  return (a > b) ? a : b; };
inline float    strict_max(float    a, float    b) {  return (a > b) ? a : b; };
inline uint32_t strict_max(uint32_t a, uint32_t b) {  return (a > b) ? a : b; };
inline uint16_t strict_max(uint16_t a, uint16_t b) {  return (a > b) ? a : b; };
inline uint8_t  strict_max(uint8_t  a, uint8_t  b) {  return (a > b) ? a : b; };
inline int32_t  strict_max(int32_t  a, int32_t  b) {  return (a > b) ? a : b; };
inline int16_t  strict_max(int16_t  a, int16_t  b) {  return (a > b) ? a : b; };
inline int8_t   strict_max(int8_t   a, int8_t   b) {  return (a > b) ? a : b; };
inline double   strict_min(double   a, double   b) {  return (a < b) ? a : b; };
inline float    strict_min(float    a, float    b) {  return (a < b) ? a : b; };
inline uint32_t strict_min(uint32_t a, uint32_t b) {  return (a < b) ? a : b; };
inline uint16_t strict_min(uint16_t a, uint16_t b) {  return (a < b) ? a : b; };
inline uint8_t  strict_min(uint8_t  a, uint8_t  b) {  return (a < b) ? a : b; };
inline int32_t  strict_min(int32_t  a, int32_t  b) {  return (a < b) ? a : b; };
inline int16_t  strict_min(int16_t  a, int16_t  b) {  return (a < b) ? a : b; };
inline int8_t   strict_min(int8_t   a, int8_t   b) {  return (a < b) ? a : b; };

/*
* Type-strict value swap.
*/
inline void strict_swap(double*   a, double*   b) {  double   t = *a; *a = *b; *b = t;  };
inline void strict_swap(float*    a, float*    b) {  float    t = *a; *a = *b; *b = t;  };
inline void strict_swap(uint32_t* a, uint32_t* b) {  uint32_t t = *a; *a = *b; *b = t;  };
inline void strict_swap(uint16_t* a, uint16_t* b) {  uint16_t t = *a; *a = *b; *b = t;  };
inline void strict_swap(uint8_t*  a, uint8_t*  b) {  uint8_t  t = *a; *a = *b; *b = t;  };
inline void strict_swap(int32_t*  a, int32_t*  b) {  int32_t  t = *a; *a = *b; *b = t;  };
inline void strict_swap(int16_t*  a, int16_t*  b) {  int16_t  t = *a; *a = *b; *b = t;  };
inline void strict_swap(int8_t*   a, int8_t*   b) {  int8_t   t = *a; *a = *b; *b = t;  };

/*
* Given two values, gives the difference between them after accounting for wrap.
*/
inline double   wrap_accounted_delta(double   a, double   b) {   return (a > b) ? (a - b) : (b - a);   };
inline float    wrap_accounted_delta(float    a, float    b) {   return (a > b) ? (a - b) : (b - a);   };
inline uint32_t wrap_accounted_delta(uint32_t a, uint32_t b) {   return (a > b) ? (a - b) : (b - a);   };
inline uint16_t wrap_accounted_delta(uint16_t a, uint16_t b) {   return (a > b) ? (a - b) : (b - a);   };
inline uint8_t  wrap_accounted_delta(uint8_t  a, uint8_t  b) {   return (a > b) ? (a - b) : (b - a);   };
inline int32_t  wrap_accounted_delta(int32_t  a, int32_t  b) {   return (a > b) ? (a - b) : (b - a);   };
inline int16_t  wrap_accounted_delta(int16_t  a, int16_t  b) {   return (a > b) ? (a - b) : (b - a);   };
inline int8_t   wrap_accounted_delta(int8_t   a, int8_t   b) {   return (a > b) ? (a - b) : (b - a);   };

#endif // __CPPPOTPOURRI_H__

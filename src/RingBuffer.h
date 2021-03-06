/*
File:   RingBuffer.h
Author: J. Ian Lindsay
Date:   2014.04.28

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


Template for a ring buffer.

TODO: Rework modulus operations into bit mask, and make element count pow(2).
TODO: Audit for best-practices for a lock-free design.
*/

#include <stdlib.h>
#include <stdint.h>

#ifndef __DS_RING_BUFFER_H
#define __DS_RING_BUFFER_H

template <class T> class RingBuffer {
  public:
    RingBuffer(const unsigned int c);  // Constructor takes the number of slots as its sole argument.
    ~RingBuffer();

    inline bool         allocated() {  return (nullptr != _pool);  };
    inline unsigned int capacity() {   return _CAPAC;              };
    inline unsigned int heap_use() {   return (_E_SIZE * _CAPAC);  };
    inline unsigned int vacancy() {    return (_CAPAC - _count);   };

    /* Returns an integer representing how many items are buffered. */
    inline unsigned int count() {      return _count;              };

    void clear();       // Wipe the buffer.
    int  insert(T);
    bool contains(T);
    T    get();
    T    get(unsigned int idx);


  private:
    const unsigned int _CAPAC;
    const unsigned int _E_SIZE;
    unsigned int _count;
    unsigned int _w;
    unsigned int _r;
    uint8_t* _pool;
};



/*
* Constructor
*/
template <class T> RingBuffer<T>::RingBuffer(const unsigned int c) : _CAPAC(c), _E_SIZE(sizeof(T)) {
  const unsigned int s = _E_SIZE * _CAPAC;
  if (0 < s) {
    _pool = (uint8_t*) malloc(s);
  }
  clear();
}


/*
* Destructor
*/
template <class T> RingBuffer<T>::~RingBuffer() {
  _count = 0;
  free(_pool);
  _pool = nullptr;
}


/**
* Drop all items from the buffer. Zeros all memory, if it is allocated.
*/
template <class T> void RingBuffer<T>::clear() {
  _w = 0;
  _r = 0;
  _count = 0;
  if (nullptr != _pool) {
    for (unsigned int i = 0; i < (_E_SIZE * _CAPAC); i++) {
      // TODO: We were almost certainly allocated on an alignment we
      // can write longwords over...
      *((uint8_t*) _pool + i) = 0x00;
    }
  }
}


/**
* This template makes copies of whatever is passed into it. There is no reason
*   for the caller to maintain local copies of data (unless T is a pointer).
*
* @return 0 on success, or negative on error.
*/
template <class T> int RingBuffer<T>::insert(T d) {
  if (_count >= _CAPAC) {
    return -1;
  }
  T* ref = &d;

  unsigned int offset = _E_SIZE * _w;
  for (unsigned int i = 0; i < _E_SIZE; i++) {
    *((uint8_t*) _pool + offset + i) = *((uint8_t*)ref + i);
  }
  _w = (_w % _CAPAC) + 1;   // TODO: Convert to pow(2) later and convert to bitmask.
  _count++;
  return 0;
}


/**
* This template makes copies of whatever is passed into it. There is no reason
*   for the caller to maintain local copies of data (unless T is a pointer).
*
* @return 0 on success, or negative on error.
*/
template <class T> bool RingBuffer<T>::contains(T d) {
  if (0 < _count) {
    unsigned int cur_idx = _r;
    uint8_t* compare = (uint8_t*) &d;
    while (cur_idx != _w) {
      uint8_t* current = (uint8_t*) (_pool + (cur_idx * _E_SIZE));
      for (uint i = 0; i < _E_SIZE; i++) {
        if (*(current + i) != *(compare + i)) {
          return true;
        }
      }
      cur_idx = (cur_idx % _CAPAC) + 1;   // TODO: Convert to pow(2) later and convert to bitmask.
    }
  }
  return false;
}



/**
* Remove and return the head of the ring.
*
* @return T(0) on failure, or the data at the front of the ring.
*/
template <class T> T RingBuffer<T>::get() {
  if (0 == _count) {
    return (T)0;
  }
  T *return_value = (T*) (_pool + (_r * _E_SIZE));
  _r = (_r % _CAPAC) + 1;   // TODO: Convert to pow(2) later and convert to bitmask.
  _count--;
  return *return_value;
}


/**
* Peek at a specific index in the ring without changing anything.
*
* @return T(0) on failure, or the data at the given index.
*/
template <class T> T RingBuffer<T>::get(unsigned int idx) {
  if ((0 == _count) || (idx > _CAPAC)) {
    return (T)0;
  }
  T* return_value = (T*) (_pool + (idx * _E_SIZE));
  return *return_value;
}

#endif // __DS_RING_BUFFER_H

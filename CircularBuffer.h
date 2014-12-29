/*
 * Copyright (c) 2014, Majenko Technologies
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 * 
 * * Neither the name of Majenko Technologies nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _CIRCULAR_BUFFER_H
#define _CIRCULAR_BUFFER_H

#if (ARDUINO >= 100) 
# include "Arduino.h"
#else
# include "WProgram.h"
#endif

template <class T> class CircularBuffer {
    private:
        T *_data;
        uint32_t _head;
        uint32_t _tail;
        uint32_t _size;

    public:
        CircularBuffer(uint32_t);
        T read();
        void write(T);
        int available();
        void clear();
        T getEntry(uint32_t p);
        uint32_t getHead();
        uint32_t getTail();
};

template <class T> CircularBuffer<T>::CircularBuffer(uint32_t size) {
    _size = size;
    _data = (T *)malloc(size * sizeof(T));
    _head = 0;
    _tail = 0;
}

template <class T> T CircularBuffer<T>::read() {
    T chr;
    if (_head == _tail) {
        return 0;
    }
    chr = _data[_tail];
    _tail = (_tail + 1) % _size;
    return chr;
}

template <class T> void CircularBuffer<T>::write(T d) {
    uint32_t newhead = (_head + 1) % _size;
    if (newhead != _tail) {
        _data[_head] = d;
        _head = newhead;
    }
}

template <class T> int CircularBuffer<T>::available() {
    return (_size + _head - _tail) % _size;
}

template <class T> void CircularBuffer<T>::clear() {
    _head = _tail = 0;
}

template <class T> T CircularBuffer<T>::getEntry(uint32_t p) {
    if (p >= _size) {
        return 0;
    }
    return _data[p];
}

template <class T> uint32_t CircularBuffer<T>::getHead() {
    return _head;
}

template <class T> uint32_t CircularBuffer<T>::getTail() {
    return _tail;
}


#endif

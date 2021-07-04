//
//  PianoSynth
//  A piano synthesizer.
//  Copyright Patrick Huang 2021
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#include <iostream>
#include <fstream>
#include "struct.hpp"


namespace Struct {
    UCH buflen(const UCH& type) {
        switch (type) {
            case (INT8):    return 1;
            case (INT16):   return 2;
            case (INT32):   return 4;
            case (INT64):   return 8;
            case (FLOAT32): return 4;
            case (FLOAT64): return 8;
            default:        return 1;
        }
    }

    void* numptr(const UCH& type, const bool& sign) {
        void* ptr = nullptr;
        if (sign) {
            switch (type) {
                case (INT8):    {char      x; ptr = &x; break;}
                case (INT16):   {short     x; ptr = &x; break;}
                case (INT32):   {int       x; ptr = &x; break;}
                case (INT64):   {long long x; ptr = &x; break;}
                case (FLOAT32): {float     x; ptr = &x; break;}
                case (FLOAT64): {double    x; ptr = &x; break;}
                default:        {char      x; ptr = &x; break;}
            }
        } else {
            switch (type) {
                case (INT8):    {unsigned char      x; ptr = &x; break;}
                case (INT16):   {unsigned short     x; ptr = &x; break;}
                case (INT32):   {unsigned int       x; ptr = &x; break;}
                case (INT64):   {unsigned long long x; ptr = &x; break;}
                case (FLOAT32): {         float     x; ptr = &x; break;}
                case (FLOAT64): {         double    x; ptr = &x; break;}
                default:        {unsigned char      x; ptr = &x; break;}
            }
        }
        //TODO fix floats
        if ((type == FLOAT32) || (type == FLOAT64)) std::cout << "FLOATS ARE STILL BUGGY" << std::endl;
        return ptr;
    }

    bool endianness() {
        const short x = 1;
        const char  b1 = *((char*)&x);
        return (b1 == 0) ? BE : LE;
    }

    void* unpack(const char* buffer, const bool endian, const bool sign, const UCH type) {
        const bool direction = (endianness() == endian);   // true = in order, false = in reverse order
        const UCH len = buflen(type);
        void* ptr = numptr(type, sign);

        for (UCH i = 0; i < len; i++) {
            const UCH offset = (direction ? i : (len-i-1));
            char* byte = ((char*)ptr + offset);
            std::cout << +(*byte) << std::endl;
            *byte = buffer[i];
        }

        return ptr;
    }

    void* unpacks(std::ifstream& stream, const bool endian, const bool sign, const UCH type) {
        const UCH len = buflen(type);
        char buffer[8];
        stream.read(buffer, len);
        return unpack(buffer, endian, sign, type);
    }
}

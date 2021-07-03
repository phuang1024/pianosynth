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

#include <fstream>
#include "struct.hpp"


namespace Struct {
    unsigned char buflen(const unsigned char& type) {
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

    void* numptr(const unsigned char& type) {
        void* ptr = nullptr;
        switch (type) {
            case (INT8):    char      x; ptr = &x; break;
            case (INT16):   short     x; ptr = &x; break;
            case (INT32):   int       x; ptr = &x; break;
            case (INT64):   long long x; ptr = &x; break;
            case (FLOAT32): float     x; ptr = &x; break;
            case (FLOAT64): double    x; ptr = &x; break;
            default:        char      x; ptr = &x; break;
        }
        return ptr;
    }
}

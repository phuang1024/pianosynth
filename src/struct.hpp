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


namespace Struct {
    // Endianness
    const bool LE = false;
    const bool BE = true;

    // Types
    const unsigned char INT8    = 0;
    const unsigned char INT16   = 1;
    const unsigned char INT32   = 2;
    const unsigned char INT64   = 3;
    const unsigned char FLOAT32 = 4;
    const unsigned char FLOAT64 = 5;

    // Sign
    const bool UNSIGNED = false;
    const bool SIGNED   = true;

    // Conversions and internal functions
    unsigned char buflen(const unsigned char&);
    void* numptr(const unsigned char&);
}

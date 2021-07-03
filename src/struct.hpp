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
    typedef  unsigned char       UCH;
    typedef  unsigned long long  ULL;

    // Endianness
    const bool LE = false;
    const bool BE = true;

    // Sign
    const bool UNSIGNED = false;
    const bool SIGNED   = true;

    // Types
    const UCH INT8    = 0;
    const UCH INT16   = 1;
    const UCH INT32   = 2;
    const UCH INT64   = 3;
    const UCH FLOAT32 = 4;
    const UCH FLOAT64 = 5;

    // Conversions and internal functions
    UCH buflen(const UCH&);
    void* numptr(const UCH&);
    bool endianness();

    // Functions that the user should use
    void* unpack(const char*, const bool, const bool, const UCH);
    void* unpacks(std::ifstream&, const bool, const bool, const UCH);
}

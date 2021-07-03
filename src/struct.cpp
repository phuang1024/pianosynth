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
    void w_int8(std::ofstream& stream, const char& value)                 {stream.write((char*)&value, 1);}
    void w_uint8(std::ofstream& stream, const unsigned char& value)       {stream.write((char*)&value, 1);}
    void w_int16(std::ofstream& stream, const short& value)               {stream.write((char*)&value, 2);}
    void w_uint16(std::ofstream& stream, const unsigned short& value)     {stream.write((char*)&value, 2);}
    void w_int32(std::ofstream& stream, const int& value)                 {stream.write((char*)&value, 4);}
    void w_uint32(std::ofstream& stream, const unsigned int& value)       {stream.write((char*)&value, 4);}
    void w_int64(std::ofstream& stream, const long long& value)           {stream.write((char*)&value, 8);}
    void w_uint64(std::ofstream& stream, const unsigned long long& value) {stream.write((char*)&value, 8);}
}

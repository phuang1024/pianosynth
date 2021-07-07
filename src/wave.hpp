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

#pragma once

#include <fstream>
#include <string>

typedef  unsigned char   UCH;
typedef  unsigned int    UINT;
typedef  unsigned short  USHORT;


class Wave {
public:
    ~Wave();
    Wave(const std::string, const UINT);

    void close();

private:
    void _write_header();

    std::ofstream* _file;
    UINT _nframes;

    UINT _fps;
    UCH _sampwidth;
    UCH _nchannels;
};

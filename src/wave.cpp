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
#include "wave.hpp"


Wave::~Wave() {
}

Wave::Wave(const std::string fname) {
    std::ofstream file(fname);
    _file = &file;
    _frames_written = 0;
}

void Wave::close() {
    _write_header();
    _file->close();
}

void Wave::_write_header() {
    _file->write("RIFF", 4);
}

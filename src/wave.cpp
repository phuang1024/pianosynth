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


// TODO endianness, i.e. swap endian dependent on machine endianness.

void write_uint(std::ofstream* stream, const UINT v) {
    stream->write((char*)&v, sizeof(UINT));
}

void write_ushort(std::ofstream* stream, const USHORT v) {
    stream->write((char*)&v, sizeof(USHORT));
}

void write_str(std::ofstream* stream, const char* str, const UINT len) {
    stream->write(str, len);
}


Wave::~Wave() {
}

Wave::Wave(const std::string fname, const UINT fps) {
    std::ofstream file(fname);

    _file = &file;
    _nframes = 0;

    _fps = fps;
    _sampwidth = 4;
    _nchannels = 1;

    _file->seekp(40, std::ios::beg);
}

void Wave::writeframe(const UINT samp) {
    const char* ptr = (char*)&samp;
    _file->write(ptr, _sampwidth);
    _nframes++;
}

void Wave::close() {
    _write_header();
    _file->close();
}

void Wave::_write_header() {
    _file->seekp(0, std::ios::beg);

    write_str(_file, "RIFF", 4);
    write_uint(_file, 36 + _nframes*_nchannels*_sampwidth);
    write_str(_file, "WAVE", 4);
    write_str(_file, "fmt ", 4);
    write_uint(_file, 16);
    write_ushort(_file, 1);
    write_ushort(_file, _nchannels);
    write_uint(_file, _fps);
    write_uint(_file, _nchannels*_fps*_sampwidth);
    write_ushort(_file, _nchannels*_sampwidth);
    write_ushort(_file, _sampwidth*8);
    write_str(_file, "data", 4);
}

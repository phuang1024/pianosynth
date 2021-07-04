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
#include <cassert>
#include <cstring>
#include "midi.hpp"
#include "struct.hpp"

using Struct::BE;
using Struct::LE;

using Struct::SIGNED;
using Struct::UNSIGNED;

using Struct::INT8;
using Struct::INT16;
using Struct::INT32;
using Struct::INT64;
using Struct::FLOAT32;
using Struct::FLOAT64;


namespace Midi {
    UCH read_byte(std::ifstream& stream) {
        char byte;
        stream.read(&byte, 1);
        return byte;
    }

    ULL read_int(std::ifstream& stream) {
        ULL value = 0;
        while (true) {
            const UCH byte = read_byte(stream);
            if ((byte&128) == 0) return value;
            value = (value<<7) + (byte&127);
        }
    }

    void read_track(MidiTrack* track, std::ifstream& stream) {
        // Read "MTrk"
        stream.seekg(4, std::ios::cur);

        const UINT size = *(int*)Struct::unpacks(stream, BE, UNSIGNED, INT32);
        while (true) {
            const ULL delta = read_int(stream);
            const UCH status = read_byte(stream);
        }

    }

    void loads(MidiFile* mid, std::ifstream& stream) {
        // Read "MThd"
        stream.seekg(4, std::ios::beg);

        // Read metadata
        const UINT meta_len = *(int*)Struct::unpacks(stream, BE, UNSIGNED, INT32);
        mid->type           = *(short*)Struct::unpacks(stream, BE, SIGNED, INT16);
        mid->num_tracks     = *(short*)Struct::unpacks(stream, BE, SIGNED, INT16);
        mid->ticks_per_beat = *(short*)Struct::unpacks(stream, BE, SIGNED, INT16);
        stream.seekg(meta_len-6, std::ios::cur);

        // Read tracks
        mid->tracks = new MidiTrack* [mid->num_tracks];
        for (UINT i = 0; i < mid->num_tracks; i++) {
            MidiTrack* track = new MidiTrack;
            read_track(track, stream);
            mid->tracks[i] = track;
        }
    }

    void loadf(MidiFile* mid, const char* path) {
        std::ifstream stream(path);
        loads(mid, stream);
    }
}

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


namespace Midi {
    void loads(MidiFile& mid, std::ifstream& stream) {
        char header[4];
        stream.read(header, 4);  // Read MThd

        const UINT meta_len = *(int*)Struct::unpacks(stream, Struct::BE, Struct::UNSIGNED, Struct::INT32);
        mid.type           = *(short*)Struct::unpacks(stream, Struct::BE, Struct::SIGNED, Struct::INT16);
        mid.num_tracks     = *(short*)Struct::unpacks(stream, Struct::BE, Struct::SIGNED, Struct::INT16);
        mid.ticks_per_beat = *(short*)Struct::unpacks(stream, Struct::BE, Struct::SIGNED, Struct::INT16);
        stream.seekg(meta_len-6, std::ios::cur);

        mid.tracks = new MidiTrack [mid.num_tracks];
    }

    void loadf(MidiFile& mid, const char* path) {
        std::ifstream stream(path);
        return loads(mid, stream);
    }
}

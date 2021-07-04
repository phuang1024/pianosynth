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
#include "struct.hpp"


struct MidiTrack {
};


struct MidiFile {
    UCH type;
    UINT num_tracks;
    UINT ticks_per_beat;

    MidiTrack** tracks;
};


namespace Midi {
    void loads(MidiFile*, std::ifstream&);
    void loadf(MidiFile*, const char*);
}

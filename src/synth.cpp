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

#define  pi       3.14159265

#include <cmath>
#include "synth.hpp"


namespace Synth {
    double sine(const double* velocities, const UINT* starts, const UINT fps,
            const UINT frame, const double pitch_lowest) {
        double value = 0;
        for (UINT i = 0; i < 88; i++) {
            const double vel = velocities[i];
            if (vel > 0) {
                const double elapse = frame - starts[i];
                const double pitch = pitch_lowest * pow(2, (double)i/12);
                const double fpc = (double)fps / pitch;   // Frames per sine cycle
                const double offset = fmod(elapse, fpc) / fpc;
                value += sin(offset*pi*2) * vel / 128;
            }
        }
        return value;
    }
}

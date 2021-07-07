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
#include <chrono>
#include "progress.hpp"


namespace Progress {
    double time() {
        const auto now = std::chrono::system_clock::now().time_since_epoch();
        const double elapse = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
        return elapse/1000;
    }

    void log(std::ostream stream, const double start, const UINT audio_fps, const UINT written) {
        const double elapse = time() - start;
        const double fps = (double)written / elapse;
        const double fac = fps / audio_fps;

        stream << "\r";
        stream << "frame=" << written << "  fps=" << fps << "  speed=" << fac << "x";
        stream << std::flush;
    }
}

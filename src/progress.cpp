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
#include <cmath>
#include <chrono>
#include <string>
#include "progress.hpp"

using std::cout;
using std::string;
using std::to_string;


string num_str(const double n) {
    if      (n < 1e3)  return to_string(n);
    else if (n < 1e6)  return to_string(n/1e3)  + "K";
    else if (n < 1e9)  return to_string(n/1e6)  + "M";
    else if (n < 1e12) return to_string(n/1e9)  + "B";
    else               return to_string(n/1e12) + "T";
}


string time_str(const double time) {
    const UINT hours = time / 3600;
    const UINT mins = fmod(time, 3600) / 60;
    const UINT secs = fmod(time, 60);
    const double milsecs = fmod(time, 1);

    string str;
    str += to_string(hours);
    str += ":";
    str += to_string(mins);
    str += ":";
    str += to_string(secs);
    str += ".";
    str += to_string(milsecs).substr(2, 3);
    return str;
}


namespace Progress {
    double time() {
        const auto now = std::chrono::system_clock::now().time_since_epoch();
        const double elapse = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
        return elapse/1000;
    }

    void log(const double start, const UINT audio_fps, const UINT written) {
        const double elapse = time() - start;
        const double fps = (double)written / elapse;
        const double fac = fps / audio_fps;

        cout << "\r";
        cout << "frame=" << num_str(written);
        cout << "  fps=" << num_str(fps);
        cout << "  speed=" << num_str(fac) << "x";
        cout << "  time=" << time_str(elapse);
        cout << std::flush;
    }
}

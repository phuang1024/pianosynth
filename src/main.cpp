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

#define  INT_MAX  2147483648
#define  pi       3.14159265

#define  VEL_THRES  1

#include <iostream>
#include <cmath>
#include <string>
#include "synth.hpp"
#include "progress.hpp"
#include "wave.hpp"

using std::cin;
using std::cout;

typedef  unsigned char  UCH;
typedef  unsigned int   UINT;


struct Message {
    UINT frame;
    UINT note;
    UINT velocity;
};


void read_msgs(Message* msgs, const UINT num_msgs) {
    for (UINT i = 0; i < num_msgs; i++) {
        UINT frame, note, vel;
        cin >> frame >> note >> vel;

        Message msg;
        msg.frame = frame;
        msg.note = note-21;
        msg.velocity = vel;
        msgs[i] = msg;
    }
}


void write_audio(Wave& wave, const Message* msgs, const UINT num_msgs, const UINT fps,
        const double tuning, const double volume) {
    const double pitch_lowest = tuning / 16;
    const double vol_fac = pow(0.5, 1.0/fps);
    const double start = Progress::time();

    UINT next_msg = 0;
    UINT starts[88];
    double velocities[88];
    for (UINT i = 0; i < 88; i++)
        velocities[i] = 0;

    UINT frame = 0;
    double last_log = 0;

    while (true) {
        if (next_msg < num_msgs) {
            if (frame >= msgs[next_msg].frame) {
                const UINT note = msgs[next_msg].note;
                velocities[note] = msgs[next_msg].velocity;
                starts[note] = frame;
                next_msg++;
            }
        }

        const double value = Synth::sine(velocities, starts, fps, frame, pitch_lowest);
        const int samp = value*volume*INT_MAX;
        wave.writeframe(samp);

        const double time = Progress::time();
        if (time >= last_log+0.5) {
            Progress::log(start, fps, frame);
            last_log = time;
        }

        // for (double& vel: velocities) {
        //     vel = vel*vol_fac;
        //     if (vel < VEL_THRES) vel = 0;
        // }

        if (next_msg >= num_msgs) {
            bool all_zero = true;
            for (double& vel: velocities) {
                if (vel > 0) {
                    all_zero = false;
                    break;
                }
            }
            if (all_zero)
                break;
        }

        frame++;
    }

    wave.close();
    cout << std::endl;
}


int main(const int argc, const char** argv) {
    cout << std::fixed;

    const std::string fname = argv[1];
    const UINT fps = std::stoi(argv[2]);
    const double tuning = std::stod(argv[3]);
    const double volume = std::stod(argv[4]);

    UINT num_msgs;
    cin >> num_msgs;

    Message* msgs = new Message [num_msgs];
    Wave wave(fname, fps);

    read_msgs(msgs, num_msgs);
    write_audio(wave, msgs, num_msgs, fps, tuning, volume);
}

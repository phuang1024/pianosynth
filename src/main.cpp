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
        cout << std::endl;

        Message msg;
        msg.frame = frame;
        msg.note = note-21;
        msg.velocity = vel;
        msgs[i] = msg;
    }
}


void write_audio(const Message* msgs, const UINT num_msgs, const UINT fps, const double tuning, const double volume) {
    const double pitch_lowest = tuning / 16;
    const double vol_fac = pow(0.5, 1.0/fps);

    UINT   next_msg = 0;
    UINT   starts[88];
    double velocities[88];
    for (UINT i = 0; i < 88; i++)
        velocities[i] = 0;

    UINT frame = 0;
    while (true) {
        if (next_msg < num_msgs) {
            if (frame >= msgs[next_msg].frame) {
                const UINT note = msgs[next_msg].note;
                velocities[note] = msgs[next_msg].velocity;
                starts[note] = frame;
                next_msg++;
            }
        }

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
        //TODO write into wave file here
        cout << (int)(value*volume*INT_MAX) << std::endl;

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
            if (all_zero) break;
        }

        frame++;
    }
}


int main(const int argc, const char** argv) {
    const UINT fps = std::stoi(argv[1]);
    const double tuning = std::stod(argv[2]);
    const double volume = std::stod(argv[3]);

    UINT num_msgs;
    cin >> num_msgs;
    Message* msgs = new Message [num_msgs];

    read_msgs(msgs, num_msgs);
    write_audio(msgs, num_msgs, fps, tuning, volume);
}

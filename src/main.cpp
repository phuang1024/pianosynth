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

using std::cin;
using std::cout;

typedef  unsigned char  UCH;
typedef  unsigned int   UINT;


struct Message {
    UINT frame;
    UINT velocity;
};


void read_msgs(Message* msgs, const UINT num_msgs) {
    for (UINT i = 0; i < num_msgs; i++) {
        UINT frame, vel;
        cin >> frame >> vel;

        Message msg;
        msg.frame = frame;
        msg.velocity = vel;
        msgs[i] = msg;
    }
}


int main() {
    UINT num_msgs;
    cin >> num_msgs;

    Message* msgs = new Message [num_msgs];
    read_msgs(msgs, num_msgs);
}

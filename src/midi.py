#
#  PianoSynth
#  A piano synthesizer written in Python.
#  Copyright Patrick Huang 2021
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

import mido
import numpy as np


def parse_midi(path, fps):
    msgs = []
    curr_time = 0
    for msg in mido.MidiFile(path):
        curr_time += msg.time*fps
        msgs.append((int(curr_time), msg))

    return msgs


def note_vels(msgs, fps):
    vels = np.zeros((88,), dtype=np.float32)
    starts = np.zeros((88,), dtype=np.float32)
    frame = 0

    fac = 0.75 ** (1/fps)
    thres = 0.01
    msgs = msgs.copy()

    while True:
        if frame >= msgs[0][0]:
            msg = msgs.pop(0)[1]
            if msg.type in ("note_on", "note_off"):
                note = msg.note - 21
                vel = 0 if msg.type == "note_off" else msg.velocity
                vels[note] = vel
                starts[note] = frame

        vels = vels * fac
        vels[vels<thres] = 0

        yield (vels, starts)

        if len(msgs) == 0 and not np.any(vels):
            break

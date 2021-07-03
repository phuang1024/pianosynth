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

import math


def synthesize(fps, tuning, frame, vels, starts):
    value = 0
    pitch_lowest = tuning / 16

    for i in range(88):
        vel = vels[i]
        if vel > 0:
            elapse = frame - starts[i]
            pitch = pitch_lowest * 2**(i/12)
            fpc = fps / pitch   # Frames per sine wave cycle
            offset = elapse % fpc
            value += math.sin(offset) * vel / 128

    return value

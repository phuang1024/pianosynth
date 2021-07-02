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

import struct


class SoundPrint:
    def __init__(self, path):
        self.notes = {}

        with open(path, "rb") as file:
            num = struct.unpack("<I", file.read(4))[0]
            for _ in range(num):
                note, mode = file.read(2)
                vol, freq = struct.unpack("ff", file.read(8))[0]
                #TODO read note data

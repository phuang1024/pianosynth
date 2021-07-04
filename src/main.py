#
#  PianoSynth
#  A piano synthesizer.
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

import os
import subprocess
import argparse
import mido

PARENT = os.path.dirname(os.path.realpath(__file__))


def parse_midi(path, fps):
    msgs = []
    curr_time = 0
    for msg in mido.MidiFile(path):
        curr_time += msg.time*fps
        msgs.append((int(curr_time), msg))

    return msgs


def main():
    parser = argparse.ArgumentParser(description="A piano synthesizer")
    parser.add_argument("-i", "--input", required=True, help="Input MIDI file.")
    parser.add_argument("-o", "--output", required=True, help="Output Wave file.")
    args = parser.parse_args()

    fps = 44100
    msgs = parse_midi(args.input, fps)

    proc = subprocess.Popen([os.path.join(PARENT, "psynth_cpp")], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    proc.stdin.write(str(len(msgs)).encode())
    proc.stdin.write(b"\n")
    for t, msg in msgs:
        if msg.type in ("note_on", "note_off"):
            vel = 0 if msg.type == "note_off" else msg.velocity
            proc.stdin.write(str(int(t*fps)).encode())
            proc.stdin.write(b" ")
            proc.stdin.write(str(vel).encode())
            proc.stdin.write(b"\n")


main()

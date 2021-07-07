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

import sys
import os
import signal
import subprocess
import argparse
import mido

INT_MIN = -2147483648
INT_MAX = 2147483647

PARENT = os.path.dirname(os.path.realpath(__file__))


def bounds(v, vmin, vmax):
    return max(min(v, vmax), vmin)


def parse_midi(path, fps):
    msgs = []
    curr_time = 0
    for msg in mido.MidiFile(path):
        curr_time += msg.time*fps
        msgs.append((int(curr_time), msg))

    return msgs


def main():
    signal.signal(signal.SIGPIPE, signal.SIG_DFL)

    parser = argparse.ArgumentParser(description="A piano synthesizer")
    parser.add_argument("-i", "--input", required=True, help="Input MIDI file.")
    parser.add_argument("-o", "--output", required=True, help="Output Wave file.")
    parser.add_argument("-t", "--tuning", type=int, default=441, help="Frequency of A4.")
    parser.add_argument("-v", "--volume", type=float, default=0.5, help="Volume multiplier.")
    args = parser.parse_args()

    fps = 44100
    msgs = parse_midi(args.input, fps)
    num_good = len(list(filter((lambda m: m[1].type in ("note_on", "note_off")), msgs)))

    proc_args = [os.path.join(PARENT, "psynth_cpp"), args.output, str(fps), str(args.tuning), str(args.volume)]
    proc = subprocess.Popen(proc_args, stdin=subprocess.PIPE, stdout=sys.stdout, stderr=sys.stderr)
    proc.stdin.write(f"{num_good}\n".encode())
    for t, msg in msgs:
        if msg.type in ("note_on", "note_off"):
            proc.stdin.write(f"{t}\n".encode())
            proc.stdin.write(f"{msg.note}\n".encode())
            proc.stdin.write(f"{msg.velocity}\n".encode())
    proc.stdin.flush()
    proc.wait()


main()

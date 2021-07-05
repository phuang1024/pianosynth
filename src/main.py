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
import time
import signal
import struct
import subprocess
import wave
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
    signal.signal(signal.SIGPIPE, signal.SIG_DFL)

    parser = argparse.ArgumentParser(description="A piano synthesizer")
    parser.add_argument("-i", "--input", required=True, help="Input MIDI file.")
    parser.add_argument("-o", "--output", required=True, help="Output Wave file.")
    args = parser.parse_args()

    fps = 44100
    msgs = parse_midi(args.input, fps)
    num_good = len(list(filter((lambda m: m[1].type in ("note_on", "note_off")), msgs)))

    proc = subprocess.Popen([os.path.join(PARENT, "psynth_cpp")], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    proc.stdin.write(f"{num_good}\n".encode())
    for i, (t, msg) in enumerate(msgs):
        if msg.type in ("note_on", "note_off"):
            proc.stdin.write(f"{t}\n".encode())
            proc.stdin.write(f"{msg.note}\n".encode())
            proc.stdin.write(f"{msg.velocity}\n".encode())
    proc.stdin.flush()

    with wave.Wave_write(args.output) as file:
        file.setframerate(fps)
        file.setnchannels(1)
        file.setsampwidth(4)

        while proc.poll() is None:
            data = proc.stdout.read(4)
            if len(data) < 4:
                proc.stdout.seek(-len(data), os.SEEK_CUR)
                time.sleep(0.01)
                continue
            file.writeframesraw(data)


main()

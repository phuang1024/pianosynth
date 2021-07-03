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

import os
import argparse
import struct
import wave
import midi
import synth

INT_MAX = 2 ** 31


def main():
    parser = argparse.ArgumentParser(description="A piano synthesizer")
    parser.add_argument("-i", "--input", required=True, help="Input MIDI file.")
    parser.add_argument("-o", "--output", required=True, help="Output .wav file path.")
    parser.add_argument("-s", "--soundprint", required=True, help="SoundPrint file.")
    parser.add_argument("-t", "--tuning", type=float, help="Frequency of A4 (default 441)", default=441)
    parser.add_argument("-v", "--volume", type=float, help="Volume multiplier", default=1)
    args = parser.parse_args()

    if os.path.isfile(args.output) and \
            input(f"Output {args.output} exists. Overwrite? [y/N] ").lower().strip() != "y":
        return

    fps = 44100
    msgs = midi.parse_midi(args.input, fps)

    audio: wave.Wave_write   # Type hinting
    with wave.open(args.output, "w") as audio:
        audio.setnchannels(1)
        audio.setsampwidth(4)   # 32 bit audio
        audio.setframerate(fps)

        for i, (vels, starts) in enumerate(midi.note_vels(msgs, fps)):
            value = synth.synthesize(fps, args.tuning, i, vels, starts)
            value = int(value*INT_MAX*args.volume/4)
            audio.writeframesraw(struct.pack("<i", value))

            if i % fps == 0:
                print(i//fps)


main()

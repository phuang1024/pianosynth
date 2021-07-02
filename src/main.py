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
import numpy as np


def main():
    parser = argparse.ArgumentParser(description="A piano synthesizer")
    parser.add_argument("-i", "--input", required=True, help="Input MIDI file.")
    parser.add_argument("-o", "--output", required=True, help="Output .wav file path.")
    args = parser.parse_args()

    assert args.output.endswith(".wav"), "Output file must end with .wav"
    assert args.input.endswith((".mid", ".midi")), "Input file must end with .mid or .midi"
    if os.path.isfile(args.output) and \
            input(f"Output {args.output} exists. Overwrite? [y/N] ").lower().strip() != "y":
        return

    fps = 44100

    audio: wave.Wave_write   # Type hinting
    with wave.open(args.output, "w") as audio:
        audio.setnchannels(1)
        audio.setsampwidth(4)   # 32 bit audio
        audio.setframerate(fps)


main()

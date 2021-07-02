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

import argparse
import wave


def main():
    parser = argparse.ArgumentParser(description="A piano synthesizer")
    parser.add_argument("-i", "--input", action="append", help="Input MIDI files.")
    parser.add_argument("-o", "--output", required=True, help="Output .wav file path.")
    args = parser.parse_args()

    assert args.output.endswith(".wav"), "Output file must end with .wav"
    assert args.input is not None, "At least one input is required."
    print(args.input)


main()

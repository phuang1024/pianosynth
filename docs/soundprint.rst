SoundPrint
==========

SoundPrints are PianoSynth's version of sound fonts.
We recommend naming a SoundPrint file with a ``.sp`` extension.

SoundPrint Structure
--------------------

The start of a SoundPrint file has a 32-bit little endian unsigned
integer, specifying how many notes are defined. A standard piano
has 88 playable notes.

After that, define each note as follows:

- One byte specifying the MIDI note (the lowest note on piano is 21).
- One byte specifying the note type:
    - ``0``: The note is an empty note (no sound)
    - ``1``: A sum of pure sine waves, with hard-coded amplitudes
      and frequencies dependent on the base note frequency.
    - ``2``: It is identical to another note. Circular dependencies
      will raise an error.
- A 32-bit float specifying the volume multiplier
- A 32-bit float specifying the frequency multiplier
- The note data:
    - If ``type == 0``:
        No data
    - If ``type == 1``:
        - A 32-bit little endian unsigned integer, specifying how many
          individual frequencies there are.
        - For each frequency:
            - A 32-bit float specifying the multiplier of this frequency
              to the base frequency.
            - A 32-bit float specifying the volume multiplier for this frequency.
    - If ``type == 2``:
        - A 32-bit little endian unsigned integer, specifying the target
          note.

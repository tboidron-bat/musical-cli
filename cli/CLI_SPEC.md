# musical-cli — Command Specification

This document defines the terminal commands planned for musical-cli.

---

## Scale

### Show a scale

scale <tonic> <scale_name>

Example:
scale A harmonic_minor


### Show modes of a scale

scale <tonic> <scale_name> --modes

Example:
scale A harmonic_minor --modes

## Chord

### Parse a chord

chord "<chord_symbol>"

Example:
chord Cm7

---

### Analyse chord in a key

musical-cli analyse "<chord_symbol>" --key <key>

Example:
musical-cli analyse "G7" --key C

---

## Guitar

### Show guitar diagram (ASCII)

musical-cli guitar "<chord_symbol>"

Example:
musical-cli guitar "Am"

---

## Future ideas

- Roman numeral analysis
- Modal interchange detection
- Secondary dominant detection
- Chord progression analysis

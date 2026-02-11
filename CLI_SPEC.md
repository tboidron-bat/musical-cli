# musical-cli — Command Specification

This document defines the terminal commands planned for musical-cli.

---

## Scale

### Show a scale

musical-cli scale <tonic> <scale_name>

Example:
musical-cli scale A harmonic_minor

---

### Show modes of a scale

musical-cli scale <tonic> <scale_name> --modes

Example:
musical-cli scale A harmonic_minor --modes

---

## Chord

### Parse a chord

musical-cli chord "<chord_symbol>"

Example:
musical-cli chord "Cm7"

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

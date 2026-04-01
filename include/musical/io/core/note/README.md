# Chord

Ce dossier regroupe tout ce qui concerne la représentation, la construction,
la manipulation et l’affichage des accords musicaux dans le moteur
**musical-core**.



---

## Responsabilités

Le module `Chord` est responsable de :

- la représentation d’un accord en tant qu’objet musical (`Chord`)
- le parsing et le formatage des symboles d’accords
- la génération de diagrammes d’accords pour instruments à cordes (guitare)

Ce module **ne fait pas d’analyse musicale avancée** (celle-ci est déléguée
au dossier `analysis`).

---

### Parsing et formatage

- `io::chord::parser`  
  Conversion d’une représentation textuelle (ex : `Cm7`, `G7(b9)`) en
  structure `Chord`.

- `io::chord::formatter`  
  Génération de représentations textuelles lisibles à partir d’un `Chord`.


---

### Diagrammes de guitare

Sous-dossier `guitar/` :

- `chord_guitar_diagram`  
  Interface générique de diagramme d’accord.

- `chord_guitar_diagram_ascii_6`  
  Rendu ASCII pour guitare 6 cordes.

---

## Dépendances

Le module `Chord` dépend de :

- `Note` et `Interval` (représentation des hauteurs)

Il **ne dépend pas** des modules :

- `analysis`
- `ScalePattern`
- `Mode`

---

## Principes de conception

- un accord est défini par des intervalles, pas par une gamme
- aucune logique d’analyse fonctionnelle dans ce module
- API orientée domaine musical, pas orientée interface utilisateur
- extensible à d’autres instruments à cordes

---

## Évolution prévue

- compatibilité avec des systèmes de notation externes (MEI, MusicXML)

---

Ce module est destiné à rester stable, car il constitue
une brique fondamentale du moteur musical.

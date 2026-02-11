# Chord

Ce dossier regroupe tout ce qui concerne la représentation, la construction,
la manipulation et l’affichage des accords musicaux dans le moteur
**musical-core**.

Il constitue le cœur du domaine harmonique du projet.

---

## Responsabilités

Le module `Chord` est responsable de :

- la représentation d’un accord en tant qu’objet musical (`Chord`)
- la construction d’accords à partir de différentes entrées (`ChordFactory`)
- la gestion des enchaînements harmoniques simples (`Cadence`)
- le parsing et le formatage des symboles d’accords
- la génération de diagrammes d’accords pour instruments à cordes (guitare)

Ce module **ne fait pas d’analyse musicale avancée** (celle-ci est déléguée
au dossier `analysis`).

---

## Contenu

### Objets principaux

- `Chord`  
  Représente un accord comme un ensemble structuré d’intervalles
  à partir d’une fondamentale.

- `ChordFactory`  
  Fabrique d’accords à partir de différentes représentations
  (symboles, degrés, structures internes).

- `Cadence`  
  Représente une suite d’accords formant un mouvement harmonique simple.

---

### Parsing et formatage

- `chord_parser`  
  Conversion d’une représentation textuelle (ex : `Cm7`, `G7(b9)`) en
  structure `Chord`.

- `chord_formatter`  
  Génération de représentations textuelles lisibles à partir d’un `Chord`.

- `chord_name`  
  Logique de nommage harmonique (qualité, tensions, altérations).

---

### Diagrammes de guitare

Sous-dossier `Guitar/` :

- `chord_guitar_diagram`  
  Interface générique de diagramme d’accord.

- `chord_guitar_diagram_ascii_6`  
  Rendu ASCII pour guitare 6 cordes.

- `chord_guitar_diagram_db_6`  
  Accès à une base de positions d’accords prédéfinies.

Ces composants dépendent de la configuration de l’instrument
(`musical::instrument::guitar::TuningType`) mais restent indépendants de l’analyse musicale.

---

## Dépendances

Le module `Chord` dépend de :

- `Note` et `Interval` (représentation des hauteurs)
- `Figure` (si la durée est associée à l’accord)

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

- ajout de diagrammes pour d’autres instruments
- enrichissement des qualités et tensions d’accords
- compatibilité avec des systèmes de notation externes (MEI, MusicXML)

---

Ce module est destiné à rester stable, car il constitue
une brique fondamentale du moteur musical.

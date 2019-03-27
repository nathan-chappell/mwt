# README.md

# Overview
This repository contains the files relevant to my work on a proof of the Minkowski-Weyl Theorem (MWT), and C++ (cpp) code relevant to an enumeration algorithm.

## Latex
The paper is written in latex, and all latex files are contained in this folder.  It is broken up into different .tex files, and this organization will probably change or be elaborated as the paper comes closer to completion.  Currently, the files currently include:
* new_commands.tex  - here are the \newcommands I'm using
* proof_diagram.tex - here is the tikz image of the diagram I'm using to guide the proof
* mwt.tex           - the main file (needs more organization)
* mwt_.\*.tex       - all sections are broken up into separate files

## cpp
src and include directories are self-explanatory

* cone_base.(cc|h)   - hcone and vcone use the same implemenation
  * hcone.(cc|h)     - *halspace cone*
  * vcone.(cc|h)     - *vector cone*
* hpolyhedron.(cc|h) - nothing yet
* vpolyhedron.(cc|h) - nothing yet
* polyhedra.(cc|h)   - gathers all the stuff together

generics.h           - the *generic* abstractions of algorithms described in the paper
mwt.h                - *Minkowski Weyl Theorem* specific code
polyhedra_common.h   - math terms, error class for input

# README.md

# Overview
This repository contains the files relevant to my work on a proof of the
Minkowski-Weyl Theorem (MWT), and C++ (cpp) code relevant to an enumeration
algorithm.

## Usage
See usage.txt for usage information

## Latex
I've taken the latex template from the university.  The files that currently
contain my work are:
* en/chap\*.tex        The chapter are broken up into separate files
* en/epliog.tex       Nothing yet 
* getlistings.sh      Script to automatically generate listingcommands.tex
* listingcommands.tex Commands for viewing source code
* macros.tex          all other user-defined macros
* preface.tex         Basic introduction
* thesis.tex          The main body, "boiler-plate"

## cpp (src,include)
* linear_algebra.{cpp,h}    Vector and Matrix, IO, basic Matrix operations
* fourier_motzkin.{cpp,h}   Fourier Motzkin elimination
* polyhedra.{cpp,h}         Transforms between polytopes and polyhedra

## testing
To test that the algorithm works for an hcone, an hcone is provided with a
precalculated minimal set of rays to generate the cone (called a key).  Then,
each ray from the transform is tested to make sure that it satisfies the
constraints of the original hcone, and a search is performed to find a ray
equivalent to each ray from the key in the new representation.  A similar idea
is used for all other transformations.
* test_functions.{cpp,h} types and functions needed to run the tests
* test.cpp               tests for the functions, and test cases to run


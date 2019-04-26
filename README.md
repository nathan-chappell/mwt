# README.md

# Overview
This repository contains the files relevant to my work on a proof of the Minkowski-Weyl Theorem (MWT), and C++ (cpp) code relevant to an enumeration algorithm.

## Latex
* mwt.tex            - the proof

## cpp (src,include)
* common.{cpp,h}            Types, matrix transpose, IO used by all other components.
* fourier_motzkin.{cpp,h}   Operations specific to Fourier Motzkin elimination.
* hcone.{cpp,h}             Functions to transform H-Cone $to$ V-Cone.
* poly_to_cone.{cpp,h}      Transforms between polytopes and polyhedra.
* transforms.{cpp,h}        All transformations.
* vcone.{cpp,h}             Functions to transform V-Cone $to$ H-Cone.

# Executable programs
* vcone_to_hcone
* vpoly_to_hpoly
* hcone_to_vcone
* hpoly_to_vpoly

## usage
input       |   | definition
hcone, vcone|:= |dimension   (vector)*
       hpoly|:= |dimension+1 (vector constraint)*
       vpoly|:= |dimension   (vector)* 'U' (vector)*

item        | description
------------|------------
dimension   |is a positive integer
vector      |is (dimension) doubles separated by whitespace
constraint  |is a double (the value b_i in <A_i,x> <= b_i)
hvector     |is (dimension) doubles separated by whitespace
'U'         |is the literal character 'U'


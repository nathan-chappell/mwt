# README.md

# Overview
This repository contains the files relevant to my work on a proof of the Minkowski-Weyl Theorem (MWT), and C++ (cpp) code relevant to an enumeration algorithm.

## Latex
* mwt.tex            - the proof

## cpp (src,include)
* common.{cpp,h}            Types, IO, and Fourier Motzkin elimination.
* hcone.{cpp,h}             Functions to transform H-Cone $to$ V-Cone.
* polyhedra.{cpp,h}         Transforms between polytopes and polyhedra.
* vcone.{cpp,h}             Functions to transform V-Cone $to$ H-Cone.

# Executable programs
* vcone_to_hcone
* vpoly_to_hpoly
* hcone_to_vcone
* hpoly_to_vpoly

## usage
The executables above read an object from stdin and writes the transformed object to stdout.<br/>

The objects are:<br/>

hcone, vcone := dimension   (vector)\* <br/>
       hpoly := dimension+1 (vector constraint)\* <br/>
       vpoly := dimension   (vector)\* 'V' (vector)\* <br/>

item        | description
------------|------------
dimension   |is a positive integer
vector      |is (dimension) doubles separated by whitespace
constraint  |is a double (the value b_i in <A_i,x> <= b_i)
'V'         |is the literal character 'V'


# SimpleGL

## What is SimpleGL?

Is a tiny grapihcs library that aims to simplify OpenGL code the most as possible.
This library is aimed to people who is starting OpenGL development and needs some abstractions to save 
lines of code while ddeply learning another concepts.

It is not aimed to be the most efficient implementation possible, so if you are advanced into graphics 
programming (or general software engineering), you may want to help to make it better :3

To sum up, this library is for new graphics programming devs that while learning concepts, need ease of 
use to avoid duplicating code. Experienced graphics programmers are welcome to help to make this 
abstraction better and more efficient.

## Special warnings

The version 1.x and earlier will depend on the glew32s.lib binary file but it is planned for this 
library to manually load itself the OpenGL functions. I honestly don't have the necessary knowledge 
(at least right now) to dynamically load the OpenGL functions.

On future versions it will be more independent.

## Tools needed to use this library

 - clang llvm compiler Technology (insert url)
 - ninja build system (Insert url)
 - ninja wrapper for python: _>pip install ninja
 - clang compiler and LLVM (If not, modify the build.py file to COMPILER = "g++" or whatever)

## Linux Installation guide

...

## Windows isntallation guide

...
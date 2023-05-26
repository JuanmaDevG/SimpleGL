# SimpleGL

## What is SimpleGL?

Is an OpenGL + glew (static) based library that aims to simplify OpenGL code the most as possible.
This library is aimed to people who is starting OpenGL development and needs some abstractions to save 
lines of code while ddeply learning another concepts.

It is not aimed to be the most efficient implementation possible, so if you are advanced into graphics 
programming, you may want to help to make it better :3

To sum up, this library is for new graphics programming devs that while learning concepts, need ease of 
use to avoid duplicating code. Experienced graphics programmers are welcome to help to make this 
abstraction better and more efficient.

## Special warnings

The version 1.x and earlier will do the bad practice of having the glew32s.lib binary file but 
it is planned for this library to manually load itself the OpenGL functions, but honestly 
I don't have the knowledge (at least right now) needed to dynamically load the OpenGL functions.

On future versions, will be more efficient and independent.

## Tools needed

 - python 3.7 or later version (Insert url)
 - ninja build system (Insert url)
 - ninja wrapper for python: _>pip install ninja
 - clang compiler and LLVM (If not, modify the build.py file to COMPILER = "g++" or whatever)
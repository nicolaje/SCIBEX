SCIBEX
======
**This project is a draft**

SCIBEX is a Server for Contractor Programming using IBEX.

It aims to enable users to easily use the powerful IBEX library for contractor programming (https://github.com/ibex-team/ibex-lib), without requiring the user to install the library.
Using the simple API SCIBEX, anybody will be able to call IBEX algorithms from their favorite programming language (C/C++, Python, Matlab...) without having to go through the hassle of writing some glue code.

Following the philosophy of VIBEs (https://github.com/ENSTABretagneRobotics/VIBES), SCIBEX consists of two parts:
- the SCIBEX server is a single executable that comes precompiled for OSX, Windows and Linux, and has IBEX statically linked inside
- the SCIBEX api consists of a single file per programming language defining the interface to send computations to the SCIBEX server and retrieve the results

For now, SCIBEX uses text files as an inter-process communication channel, but later we will move on named pipes to improve its efficiency.

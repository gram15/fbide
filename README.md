# FBIde - Freebasic IDE

FBIde is an IDE for FreeBasic compiler written in C++ with wxWidgets framework, originally written by Albert Varaksin (albeva, vongodric).
This is the clone of github repo of original project (which is derived from old sourceforge cvs). The focus of my work has been to make a real port to modern linux distro (i.e. Ubuntu 16.x or newer).

Link to the original site:  http://www.fbide.freebasic.net/

## Changes from original version 0.4.4 / 0.4.5
This version (let's call it 0.4.5.1) is a port fo FBIde from wxWidgets 2.6.2 to wxWidgets 3.0.x.
Also the support for external chm help file has been extended to linux too (using xchm). Another fix concerns the use of wchar_t, which was a bit tricky in original source code.

## Further enhancements
Since the port has been started from an old repository, I'd like to get access to the source code of 0.4.6r4 version of FBIde from its author, that's the last compiled versione released (Windows only) in order to make a working linux & wxW 3.0.x port.
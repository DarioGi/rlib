#!/bin/sh
# Run this to generate all the initial makefiles, etc.

autoreconf -vif -W all
./configure $*

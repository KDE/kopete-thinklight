#! /usr/bin/env bash
$EXTRACTRC `find . -name \*.ui -o -name \*.kcfg` >> rc.cpp
$XGETTEXT `find . -name \*.cpp` rc.cpp -o $podir/kopete-thinklight.pot
rm -f rc.cpp

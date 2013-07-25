#! /usr/bin/env bash
$EXTRACTRC `find . -name \*.ui -o -name \*.kcfg` >> rc.cpp
$XGETTEXT `find . -name \*.cpp` rc.cpp -o $podir/kcm_kopete_thinklight.pot
rm -f rc.cpp

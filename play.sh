#!/bin/bash

FREQ=${FREQ:="10000"}

./klatt -r 2 -s $FREQ $@ | (aplay -r $FREQ -c 1 -f S16_LE 2> /dev/null)

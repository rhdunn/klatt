#!/bin/sh

mkdir -p m4
ln -sf README.md README

aclocal -I m4 || exit 1

autoheader || exit 1
automake --add-missing || exit 1
autoconf || exit 1

#!/bin/sh

libtoolize --copy
aclocal
automake --add-missing --copy
autoconf


#!/usr/bin/python

from pic import *

depth=6

div= HOM(60,-19)
orb=orbit(div,depth)
simple=set(map(lambda d: d.cremred(), orb))
print simple

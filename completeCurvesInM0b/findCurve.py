
d=7

for delta in range(0, (d-1)*(d-2)/2):
    duald=d*(d-1)-2*delta
    dualk=3*d*(d-2)-6*delta
    if(2*dualk%duald ==0):
        print "{0} nodes, dual degree {1}, dual cusps {2}".format(delta,duald,dualk)

## this prints out values d, delta such that a curve of 

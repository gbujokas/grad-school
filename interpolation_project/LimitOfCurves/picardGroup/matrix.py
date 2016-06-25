from pic import *
import numpy as np

base=[H()]+ map(E,range(1,N+1))
def fromAutToMatrix(aut):
     return np.mat(map(lambda d: aut(d).data, base)).T

genMatrix=map(fromAutToMatrix, group_gen)

def fromDivToArray(D):
    return np.mat(D.data).T


def test(D):
    return genMatrix[0]*fromDivToArray(D)==fromDivToArray(group_gen[0](D))

hasharray=mat(for[
def angry(array):
    

class hashtable:
    def __init__(self):
        self.elements=[]
        self.used=set()
    def add(self,x):
        if hash(x) not in self.used:
            self.elements.append(x)
            self.used.add(hash(x))
   

def fast_orbit(div, depth):
    orbit=hashtable()
    orbit.add(fromDivToArray(div))
    
    while depth>0:
        depth=depth-1
        neworbit=hashtable()
        for x in orbit.elements:
            neworbit.add(x)
            for g in genMatrix:
                neworbit.add(g*x)
        orbit=neworbit
    return orbit.elements

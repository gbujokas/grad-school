# Computes d such that Hilb^d A^3 is reducible.

# The construction looks for ideals $I$ sandwicehd between
# m^k and m^{k+1}, where $m=(x,y,z)$

# Let V=I/m^{k+1} \subset m^k/m^{k+1} be an a dimensional
# subspace of the (k+2 \choose 2) subspace. Hence,

# d = length(k[x,y,z]/I) = length(k[x,y,z]/m^{k+1}) -a = (k+3 choose 3)-a

# If a is such that the dimension of the grasmannian G(a, dim m^k/m^{k+1}) is
# bigger than 3d, than we are done!

def choose2(n):
    return n*(n-1)/2

def choose3(n):
    return n*(n-1)*(n-2)/6

def d(a,k):
    return choose3(k+3)-a

def dimGrass(a,k):
    return a* (choose2(k+2)-a)

def hasExtraComp(a,k):
    return 3*d(a,k)<dimGrass(a,k)+3

k=1
a=0

while(not hasExtraComp(a,k)):
    a=a+1
    if(dimGrass(a,k)<0):
        k=k+1
        a=0

print "The Hilbert scheme Hilb^d(A^3) has extra components for:"
print "d=", d(a,k)
print "Looking at ideals I between m^k, m^{k+1}, where k=", k
print "and dimension I/m^{k+1} is", a
    

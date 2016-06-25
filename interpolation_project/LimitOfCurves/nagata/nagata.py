
# Compute the numerically possible -1 curves in the plane
# blown up at 10 points. For each case, compute range of
# emptiness for (d,m)

# To find (d,m) such that p_a(dH - \sum m E_i)=1, we
# solve x^2-10y^2=-1, and set
# d=(x+3)/2 and m=(y+1)/2

# The fundamental solution for
#      x^2-10 y^2 =-1
# is (3+ \sqrt{10})

class Solution:
    def __init__(self,a0=3,b0=1):
        self.a=a0
        self.b=b0
        return 
    def multByFundSol(self):
        return Solution(3*self.a+10*self.b,self.a+3*self.b)
    def nextSol(self):
        return self.multByFundSol().multByFundSol() 
    def get_d_m(self):
        return ( (self.a+3)/2, (self.b+1)/2)

def genus(d,m):
    return (d-1)*(d-2)/2 - 10*m*(m-1)/2


x=Solution()
oldNumBound=1
oldDenBound=1
for i in range(10):
    (d,m)=x.get_d_m()
    if genus(d,m)!=1:
        print "ERROR"
    print (d,m)
    numBound=20*d*m
    denBound=d*d+10*m*m
    print "Range from {num}/{den} to {num1}/{den1}".format(num=10*m, den=d,
                                                           num1=numBound, den1=denBound)
    print("{0:.15f}".format(1.0*numBound/denBound))
    print "Less than sqrt(10)", (numBound*numBound<10*denBound*denBound)
    print "Bigger than previous", (oldNumBound*denBound<numBound*oldDenBound)
    oldNumBound=numBound
    oldDenBound=denBound
    x=x.nextSol()

print "{0:.15f}".format(10**.5)

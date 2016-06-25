import logging
import datetime
now=datetime.datetime.now()
#hdlr = logging.FileHandler("./log/{str}.log".format(str=str(now)))
log = logging.getLogger('Interpolation Assistant')
# log.addHandler(hdlr) 
log.setLevel(logging.INFO)

def verbose(str):
    log.info(str)

def state(str):
    print str
    log.info(str)
    
def choose2(n):
    return n*(n-1)/2
    
class SeveriProblem(object):
    def __init__(self, degree, genus, delta):
        self.degree=degree
        self.genus=genus
        self.delta=delta

    @staticmethod
    def fromDegreeAndGenus(degree, genus):
        delta=choose2(degree-1) - genus
        return SeveriProblem(degree,genus,delta)

    @staticmethod
    def fromDegreeAndDelta(degree, delta):
        genus=choose2(degree-1) - delta
        return SeveriProblem(degree,genus,delta)

    def isValid(self):
        return (self.degree>0 and self.genus>=0 and self.delta>=0)

    def dimension(self):
        return 3*self.degree +self.genus-1
    
    def isDominant(self):
        return self.dimension()>=2*self.delta

    def __str__(self):
        return 'SeveriProblem d:{0:3d}, g:{1:3d}, delta:{2:3d}, dimension:{3:3d}'.format(self.degree, self.genus,self.delta, self.dimension())
    


def smallestValidProblemForDelta(delta):
    degree=0
    while True:
        degree=degree+1
        problem=SeveriProblem.fromDegreeAndDelta(degree,delta)
        if(problem.isValid()):
            break
    return problem

def smallestValidProblemForGenus(genus):
    degree=0
    while True:
        degree=degree+1
        problem=SeveriProblem.fromDegreeAndGenus(degree,genus)
        if(problem.isValid()):
            break
    return problem

def largestDominantProblemForGenus(genus):
    degree=0
    while True:
        degree=degree+1
        problem=SeveriProblem.fromDegreeAndGenus(degree,genus)
        if(not problem.isDominant()):
            break
        else:
            print str(problem)
    return problem

def rangeForGenus(genus):
    print "Range for genus ",
    print genus
  
    degree=0
    while True:
        degree=degree+1
        problem=SeveriProblem.fromDegreeAndGenus(degree,genus)
        if(not problem.isDominant()):
            break
        else:
            if(problem.isValid()):
                print str(problem)

for g in range(0,100):
    rangeForGenus(g)

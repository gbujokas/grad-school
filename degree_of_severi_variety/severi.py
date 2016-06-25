from collections import deque
import binomialtable

class TangencyIndex:
    # Elements of this class are multisets
    # {1^a,2^b, 3^c, ..}
    #
    # internally represented by the list [a,b,c,d,...]
    
   
    # creates the multiset {1^d}
    def __init__(self, d=0):
        self.values=[d]

    
    def __str__(self):
        self.__trimZeros()
        if(len(self.values)==1):
            return str(self.values[0])
        return str(self.values)

    #creates a hard copy
    def copy(self):
        copy=TangencyIndex()
        copy.values=list(self.values)
        return copy

    #returns the multiplicity of the integer k in the multiset
    def valueAt(self, k):
        self.__ensureLength(k)
        return self.values[k-1]

    # makes sure the internal representation can handle the element k
    # in the multiset
    def __ensureLength(self, k):
        if(len(self.values)<k):
            self.values=self.values+ [0]*(k-len(self.values))
            
    def __trimZeros(self):
        while(len(self.values)>=2 and self.values[-1]==0):
            self.values.pop()

    # returns the largest element in the multiset
    def maxTangency(self):
        self.__trimZeros()
        if len(self.values)==1 and self.values[0]==0:
            return 0
        return len(self.values)

    #inserts k in the multiset
    def add(self, k):
        self.__ensureLength(k)
        self.values[k-1]=self.values[k-1]+1

    #deletes elements k
    def subtract(self, k):
        if(len(self.values)<k):
            raise NameError('Subtracting a tangency condition that is not present')
        else:
            self.values[k-1]=self.values[k-1]-1

    #returns the number of elements in the multiset
    def numberOfPoints(self):
        return sum(self.values)

    #maps [1^a, 2^b, 3^c,..] to a+2b+3c+...
    def length(self):
        length=0
        for i, val in enumerate(self.values):
            length=length+val*(i+1)
        return length


    table = binomialtable.BinomialTable(20)
    # [1^a1,2^b1, ..].choose(1^a2, 2b^2, 3^c2,..) =
    #                    (a1 choose a2) x (b1 choose b2) x (c1 choose c2) x ...
    def choose(self, tuple):
        
        self.__trimZeros()
        tuple.__trimZeros()
        if(len(self.values)<len(tuple.values)):
            return 0
        prod=1
        for a,b in zip(self.values, tuple.values):
            prod=prod* TangencyIndex.table.binomial(a,b)
        return prod
        
        

def generatorTangencyCondition(tangency, addK, maxLength, index=1):
    if(tangency.length()+addK*index<=maxLength):
        if(addK<=0):
            yield tangency
        else:
            tangency.add(index)
            for tang in generatorTangencyCondition(tangency, addK-1, maxLength, index):
                yield tang
            tangency.subtract(index)
            for tang in generatorTangencyCondition(tangency, addK, maxLength, index+1):
                yield tang


def generatorSubsetOfLength(tangency, length, index=1):
    if(tangency.length()==length):
        yield tangency
    elif(tangency.length()- index>=length):
        if(tangency.valueAt(index)>0):
            tangency.subtract(index)
            for tang in generatorSubsetOfLength(tangency, length, index):
                yield tang
            tangency.add(index)
        for tang in generatorSubsetOfLength(tangency, length, index+1):
            yield tang
            

def test():
    tangency=TangencyIndex(4)
    for tang in generatorTangencyCondition(tangency, 3, 10):
        print tang

        tangency.add(5)
        tangency.add(3)
        tangency.add(2)
        tangency.add(2)
        print 'Subsets of '+ str(tangency)
        for tang in generatorSubsetOfLength(tangency, 4):
            print tang


class GeneralizedSeveriVariety:
    @staticmethod
    def standard( degree, delta):
        return GeneralizedSeveriVariety(degree,
                                        delta,
                                        TangencyIndex(0),
                                        TangencyIndex(degree))

    def __init__(self, degree, delta, alpha, beta):
        self.degree=degree
        self.delta=delta
        self.alpha=alpha
        self.beta=beta
    
    def __str__(self):
        return '({0},{1},{2},{3})'.format(self.degree,
                                          self.delta,
                                          str(self.alpha),
                                          str(self.beta))
    def copy(self):
        return GeneralizedSeveriVariety(self.degree,
                                        self.delta,
                                        self.alpha.copy(),
                                        self.beta.copy())

    def multiplicity(self, divisor):
        if(self.degree==divisor.degree):
            k=1
            while(self.alpha.valueAt(k)==divisor.alpha.valueAt(k)):
                k=k+1
            return k
            
        prod=1
        for k in range(1,len(divisor.beta.values)+2):
            for j in range(0,-self.beta.valueAt(k)+divisor.beta.valueAt(k)):
                prod=prod*k
        return prod*divisor.beta.choose(self.beta)

    def numberOfComponents(self,divisor):
        if(self.degree==divisor.degree):
            return 1
        return self.alpha.choose(divisor.alpha)
    
    def intersectionComponents(self):
        problem=self.copy()
        for a in problem.__intersectionComponents():
            yield a

    def deg(self):
        if self.degree==1:
            if self.delta==0:
                return 1
            else:
                return 0
        deg=0
        for comp in self.intersectionComponents():
            deg=deg+ comp.deg()*self.multiplicity(comp)*self.numberOfComponents(comp)
        return deg

    
    def __intersectionComponents(self):
        for k in range(1, self.beta.maxTangency()+1):
            if(self.beta.valueAt(k)>0):
                self.beta.subtract(k)
                self.alpha.add(k)
                yield self
                self.beta.add(k)
                self.alpha.subtract(k)

            for newDelta in range(0, self.delta+1):
                for newBeta in generatorTangencyCondition(self.beta,
                                                          self.degree-1 - (self.delta-newDelta),
                                                          self.degree-1):
                    for newAlpha in generatorSubsetOfLength(self.alpha,
                                                            self.degree-1-newBeta.length()):
                        yield GeneralizedSeveriVariety(self.degree-1,
                                                       newDelta,
                                                       newAlpha,
                                                       newBeta)


            

def presentRecursion(d, delta):
    initialProblem= GeneralizedSeveriVariety.standard(d,delta)

    print 'Describing recursion for '+str(initialProblem)
    
    queue=deque([initialProblem.copy()])    
    while(len(queue)>0):
        problem=queue.pop()
        initialProblem=problem.copy()
        print 'Expanding '+str(problem)+':'
        for var in problem.intersectionComponents():
            if(var.degree==d):
                queue.appendleft(var.copy())
            print '    {0} x {1} x < {2} >={0}x{3}x{2}={4}'.format(initialProblem.
                                                                    numberOfComponents(var),
                                                                    str(var),
                                                                    initialProblem.multiplicity(var),
                                                                    var.deg(),
                                                                    initialProblem.
                                                                    numberOfComponents(var)*
                                                                    initialProblem.multiplicity(var)*
                                                                     var.deg())
                                                                    
    

presentRecursion(3,1)

def testTupleProduct():
    tuple1= TangencyIndex(5)
    tuple1.add(2)
    tuple1.add(2)
    tuple1.add(5)
    #[5,2,0,0,1]
    tuple2=TangencyIndex(4)
    tuple2.add(2)
    #[4,1]
    print tuple1
    print tuple2
    print tuple1.choose(tuple2)

import random
random.seed()

# module picard group
# plane blownup at N points
N=10
class Divisor:
    def __init__(self, divisordata):
        self.data= divisordata
    def h(self):
        return self.data[0]
    def e(self,i):
        return self.data[i]
    def __add__(self, div):
        return Divisor(map(lambda a, b: a+b, self.data,div.data))
    def __rmul__(self, k):
        return Divisor([k*x for x in  self.data])
    def __sub__(self, div):
        return Divisor(map(lambda a, b: a-b, self.data,div.data))
    def __neg__(self):
        return (-1)*self
    def __repr__(self):
        string='{}H'.format(self.data[0])
        for i in range(1,N+1):
            string+= ' {}E{}'.format(self.data[i],i)
        return string
    def __eq__(self, div):
        return self.data==div.data
    def __hash__(self):
        return reduce(lambda a, b:(31*a +b)%7253 , self.data)
    def inter(self, div):
        return sum(map( lambda a,b,c: a*b*c, self.data, div.data, [1]+[-1]*N))
    def cremona(self,i,j,k):
        div=H()-E(i)-E(j)-E(k)
        return self+ (self.h()+self.e(i)+self.e(j)+self.e(k))*div
    def sort(self):
        return Divisor([self.data[0]]+sorted(self.data[1:]))
    def cremred(self):
        div=self.sort()
        while(div.h()+div.e(1)+div.e(2)+div.e(3)<0):
            div=div.cremona(1,2,3).sort()
        return div
    def apply_auto(self, auto):
        basis=[auto(x) for x in range(N+1)]
        return reduce(lambda a,b:a+b,
                      map(lambda a, div: a*div,
                           self.data,
                           basis),
                      ZERO())

        
    
def HOM(d,m):
    return Divisor([d]+[m]*N)

def H():
    return HOM(1,0)

def E(i):
    data=[0]*(N+1)
    data[i]=1
    return Divisor(data)

def K():
    return HOM(-3,1)

def ZERO():
    return HOM(0,0)

def F(i):
    return E(i)-K()

def cremonaTest(base, t):
    if t==0:
        return base
    else:
        i=random.randint(1,N)
        j=random.randint(1,N)
        k=random.randint(1,N)
        if(i!=j and j!=k and i!=k):
            return cremonaTest(base.cremona(i,j,k), t-1)
        else:
            return cremonaTest(base, t)


        
def auto1(i,j, k):
    # p goes to p+p_i-p_j
    # (on plane blown up at nine pts:
    #  not p_k)
    # assumes N=10
    def aut(t):
        if t==0:
            return 3*F(k)+H()+3*(E(i)-E(j))
        if t==i:
            return E(i)+(E(i)-E(j))+2*F(k)
        if t==j:
            return E(i)
        if t==k:
            return E(k)
        return E(t)+(E(i)-E(j))+F(k)
    return aut

def auto2(i,j,k, l):
    #p goes to p+(H-p_i-p_j-p_k)
    # on plane blownup at 9 points (not p_l)!
    f=F(l)
    d=H()-E(i)-E(j)-E(k)
    def aut(t):
        if t==l:
            return E(l)
        if t==0:
            return H()+3*d +2*f
        if (t==i or t==j or t==k):
            return E(t)+d
        return E(t)+d+f
    return aut

def auto3(i,j,k):
    # p goes to p_i+p_j-p
    # surface blowndown at E_k
    def aut(t):
        if(t==k):
            return E(k)
        if(t==0):
            return 3*F(k)-H()+3*(E(i)+E(j))
        d=E(i)+E(j)-E(t)
        if(t != i and t!=j):
            d=d+F(k)
        return d
    return aut
            

def triples(max):
    a=[(i,j,k)
       for i in range(1,max)
       for j in range(1,max)
       for k in range(1,max)]
    return filter( lambda (i,j,k): i!=j and j!=k and k!=i , a)

def four_tuples(max):
    a=[(i,j,k, l)
       for i in range(1,max)
       for j in range(i+1,max)
       for k in range(j+1,max)
       for l in range(1,max)]
    return filter( lambda (i,j,k,l): l!=j and l!=k and l!=i , a)


group_gen=( [(lambda div: div.apply_auto(auto1(i,j,k))) for (i,j,k) in triples(N+1)]
           +[(lambda div: div.apply_auto(auto3(i,j,k))) for (i,j,k) in triples(N+1)]
           +[(lambda div: div.apply_auto(auto2(i,j,k,l))) for (i,j,k,l) in four_tuples(N+1)]
           +[(lambda div: div.cremona(i,j,k)) for (i,j,k) in triples(N+1)])


def random_walk(div, size):
    while size>0:
        size=size-1
        div=random.choice(group_gen)(div)
    return div

def step_orbit(cur_orb):
    new_orb=cur_orb.copy()
    for x in cur_orb:
        for g in group_gen:
            new_orb.add(g(x).sort())
    return new_orb

def orbit(div, depth):
    orb=set()
    orb.add(div)
    while depth>0:
        depth=depth-1
        orb=step_orbit(orb)
    return orb


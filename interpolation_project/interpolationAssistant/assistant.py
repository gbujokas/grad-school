import logging
import datetime
now=datetime.datetime.now()
hdlr = logging.FileHandler("./log/{str}.log".format(str=str(now)))
log = logging.getLogger('Interpolation Assistant')
log.addHandler(hdlr) 
log.setLevel(logging.INFO)


def verbose(str):
    log.info(str)

def state(str):
    print str
    log.info(str)

def expectedDimension(d, m):
    return ((d+2)*(d+1)- 10*m*(m+1))/2

def arithGenus(d,m):
    return ((d-1)*(d-2) - 10*m*(m-1))/2

def expectedM(d,m):
    return 2*(10*m-3*d)+1

def partitions(n):
	# base case of recursion: zero is the sum of the empty list
	if n == 0:
		yield []
		return
		
	# modify partitions of n-1 to form partitions of n
	for p in partitions(n-1):
		yield [1] + p
		if p and (len(p) < 2 or p[1] > p[0]):
			yield [p[0] + 1] + p[1:]

def gcd(a, b):
    #assumes a and b positive
    if a==0:
        return b
    if a>b:
        return gcd (b,a)
    return gcd(b%a, a)

def lcm(a,b):
    return a*b/gcd(a,b)

def gcdPartition(p):
    # computes gcd of a list
    return reduce (gcd, p)

def lcmPartition(p):
    # assumes elements of partition are positive
    return reduce (lcm, p)

def analyseCase(d,m,M):
    verbose("M={M}".format(M=M))
    dr=d-3*M
    mr=m-M
    if (dr<0 or expectedDimension(dr,mr)<=0):
        verbose("empty system\n")
        return
    
    verbose("Residual {dr}H -{mr}E_i".format(dr=dr, mr=mr))
    verbose("Genus: {gen}".format(gen=arithGenus(dr,mr)))
    intersection=3*dr-10*mr
    verbose("{inter} intersection points".format(inter=intersection))
    verbose("Possible tangency configurations:")
    for p in partitions(intersection):
        g= arithGenus(dr,mr)+len(p)
        verbose(p)
        verbose("Genus at least {gen}".format(gen=g))
        if g>arithGenus(d,m) :
            verbose("Genus too high!")
            continue
        monoD=gcdPartition(p)
        if(dr%monoD!=0 or mr%monoD!=0) :
            verbose("Not valid by monodromy! - multiple of {d}".format(d=monoD))
            continue
        if g==arithGenus(d,m) and all([x==1 for x in p]):
            verbose("Invalid by computing ramification divisor!")
            continue
        length=lcmPartition(p)
        graph=map((lambda a: length/a), p)
        str=("\n Help! For d={degree}, m={multiplicity}, M={mult} \n"
             "Genus:{totalGenus}, Residual genus:{resGenus} \n"
             "Intersection:{inter} Tangency conditions:{part} \n"
             "Graph of the form {graph}"
            )
        str=str.format(degree=d, multiplicity=m, mult=M,
                       totalGenus=arithGenus(d,m), resGenus=arithGenus(dr,mr),
                       inter=intersection, part=p, graph=graph)
        state(str)
        s=raw_input("skip this case? ")
        state("\n")
    return

def analyse(d,m):
    state("Analysing d={deg}, m={mult}".format(deg=d, mult=m))
    verbose("Expected dimension: {dim}".format(dim=expectedDimension(d,m)))
    verbose("Arithmetic genus: {gen}".format(gen=arithGenus(d,m)))
    if (10*m<3*d):
        state("Simple degeneration works - M=0")
        return
    verbose("Expected M: {M}".format(M=expectedM(d,m)))
    
    verbose("Expected residual: {dr}H- {mr}E_i \n".format(dr=d-3*expectedM(d,m),
                                                         mr=m-expectedM(d,m)))
    verbose("By Bezout, M is at least {min}".format(min=10*m-3*d))
    str=("M is not {min}, as long as {mult}*(10h - 3 p_i) is not linear"
         "equivalent to 0 \n")
    str=str.format(mult=d-3*m, min=10*m-3*d)
    verbose(str) 
    M=10*m-3*d+1
    while M<expectedM(d,m):
          analyseCase(d,m, M)
          M=M+1
        
    state("And we are done!")
    return

def discovery():
    m=(int) (raw_input("Initial m:"))
    while(True):
        d=1
        while (10*m>=3*d):
            analyse(d,m)
            d=d+1
        state("\n")
        ans=raw_input("Continue on to m={val}? ".format(val=m+1))
        if(ans!="y"):
            break
        m=m+1
    

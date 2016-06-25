import functools
from itertools import *
from collections import defaultdict

MAXDEGREE=10

# GRUUUUUUUUUUUUUU

def makegroup(tangency, repeat=1):
	group=[0]*MAXDEGREE
	group[tangency-1]=repeat
	return tuple(group)

def mergegroups(listofgroups):
	return tuple([sum(parts) for parts in zip(*listofgroups)])

def splitelement(group):
	for (index, part) in enumerate(group):
		if part!=0:
			newgroup=group[:index]+(group[index]-1,)+group[index+1:]
			yield (index+1,newgroup,group[index])

def isempty(group):
	return all([g==0 for g in group])

def islonely(group):
	return sum(group)==1

@functools.lru_cache(maxsize=100)
def grouptable(maxdegree, maxtangency=MAXDEGREE):
	#table[deg]=list of (group,support) with this degree
	if maxtangency==1:
		return [[((0,),0)]]+[[((d,),1)] for d in range(1,maxdegree+1)]
	table=[[] for i in range(0,maxdegree+1)]
	for (deg, v) in enumerate(grouptable(maxdegree,maxtangency-1)):
		for group,support in v:
			table[deg].append((group+(0,),support))
			for k in range(1, int((maxdegree-deg)/maxtangency) +1):
				table[deg+k*maxtangency].append((group+(k,),support+1))
	return table

def subsets(mask):
	if mask==[]:
		yield []
	else:
		for subset in subsets(mask[:-1]):
			yield subset+[mask[-1]]
			if mask[-1]:
				yield subset+[False]

def nextprofiles(profile,MAXN):
	# yields (newprofile, list of (genuschange, Nchange, multiplicity))

	# rational curve
	for (index, group) in enumerate(profile):
		if not isempty(group) and not islonely(group):
			for (tangency, newgroup, choice) in splitelement(group):
				yield (profile[:index]+(newgroup,)+profile[index+1:]+(makegroup(tangency),), [(0, 0, 1)])
				#TODO multiplicities (function of choice and tangency?)
	# elliptic curve
	for subset in subsets([not isempty(group) for group in profile]):
		if any(subset):
			nodes=len([s for s in subset if s])
			def presevergroup(preserve, group):
				if preserve:
					return group
				else:
					return (0,)*len(group)
			for splitdata in product(*[splitelement(group) for (combine, group) in zip (subset,profile) if combine]):
				tau=sum([tangency for (tangency,group, mult) in splitdata])
				if tau>=2:
					for (newgroup,support) in grouptable(tau)[tau]:
						newprofile=(tuple([presevergroup(not combine,group) for (combine,group) in zip(subset, profile)])+
							(mergegroups([newgroup]+[group for (tangency,group, mult) in splitdata]),))
						yield (newprofile,[(nodes, m, 1) for m in range(1,MAXN+1)])
						#TODO multiplicities


def initialfockvector(d):
	return {(makegroup(1,d),):[(-d+1,0,1)]}

def imposepoint(vector,MAXN):
	fock=defaultdict(list)
	for profile in vector:
		for (newprofile, changedata) in nextprofiles(profile,MAXN):
			fock[newprofile]+=combinedatalist(vector[profile],changedata,MAXN)
	return fock

def combinedatalist(datalist1, datalist2,MAXN):
	return [(g1+g2,n1+n2,m1*m2) for ((g1,n1,m1),(g2,n2,m2)) in product(datalist1,datalist2) if n1+n2<=MAXN]

def endpoint(profile):
	return all([group[0]<=1 and all([g==0 for g in group[1:]]) for group in profile])

def computeseveridegrees(d, MAXN):
	print("Degree {0} and N at most {1}".format(d,MAXN))
	fockvector=initialfockvector(d)
	for n in range(1,d*(MAXN+1)):
		fockvector=imposepoint(fockvector,MAXN)
		severi=defaultdict(lambda:0.0)
		print("{0} points:".format(n))
		for profile in fockvector:
			if endpoint(profile):
				for (g,N,mult) in fockvector[profile]:
					severi[(g,N)]+=mult
		for (g,N) in severi:
			print("    g={0}, N={1}: {2}".format(g,N, severi[(g,N)]))
	print("Done!")


# PROPERTY OF GRU.
# R VERSION.

#(5,3)
#(6,2)



import operator as operator
#Prime sieve
MAX_SIEVE=4000000
is_prime=[True]*MAX_SIEVE
is_prime[0]=False
is_prime[1]=False
for k in range(0,len(is_prime)):
	if is_prime[k]:
		for multiple in range(2*k,len(is_prime),k):
			is_prime[multiple]=False

primes=[p for p in range(0,MAX_SIEVE) if is_prime[p]]

def isprime(n):
	if n<0:
		return isprime(-n)	
	if n<MAX_SIEVE:
		return is_prime[n]
	if n>(MAX_SIEVE-1)*(MAX_SIEVE-1):
		raise BaseException, "Testing too large value for primality. Raise sieve MAX"
	return not any([n%p==0  for p in primes])


def factor(n):
	if n==0:
		return [0]
	exp=[]
	for p in primes:
		count=0
		while n%p==0:
			count+=1
			n/=p
		exp.append(count)
		if n==1:
			break
	return exp

def product(numbers):
	return reduce(operator.mul, numbers,1)

def primdelta0(n):
	if n==2:
		return 3
	else:
		delta0=n*n
		for p in primes:
			if n%p==0:
				delta0/=p*p
				delta0*=(p*p-1)
		return delta0/2

#	return n*n/2 * product([1-1.0/(p*p) for p in primes if n%p==0])
#	return product([p**(2*exp-2) *(p-1)*(1+p) for (p,exp) in zip(primes,factor(n))])/2

def divisors(n):
	return [d for d in range(1,n+1) if n%d==0]

def sigma(n):
	return sum(divisors(n))	

def _odddelta1(n):
	return sum([sigma(h)*sigma(n-h) for h in range(1,(n+1)/2)])

def delta1(n):
	if n%2==0:
		return sigma(n/2)*(sigma(n/2)+1)/2 + _odddelta1(n)
	else:
		return _odddelta1(n)

def primdelta1(n):
	if n==1:
		return 0
	return delta1(n) - sum([primdelta1(n/d)*sigma(d) for d in divisors(n) if not d==1])

def valid(d):
	return 12*primdelta1(d)==(5*d-6)*primdelta0(d)

print all([valid(d) for d in range(2,100)])

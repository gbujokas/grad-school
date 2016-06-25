
large=100
breakpoint=10

def special(a,b,k1,k2):
	return (5*k1-2*a)*(5*k2-2*b)*(a+b)==3*a*a*(5*k2-2*b)+3*b*b*(5*k1-2*a) and (5*k1-2*a)!=0 and (5*k2-2*b)!=0

def find():
	counter=0
	for k1 in range(1, large):
		for k2 in range(k1,large):
			for a in range(2*k1,3*k1):
				for b in range(2*k2,3*k2):
					if special(a,b,k1,k2):
						counter+=1
						if counter>=breakpoint:
							return
						print(a,b,k1,k2)

find()

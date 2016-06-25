# module picard group
# plane blownup at n points
N=10
class Divisor:
    def __init__(self, divisordata):
        self.data= divisordata
    def h(self):
        return data[0]
    def e(self,i):
        return data[i]
    def sum(self, div):
        return Divisor(map(lambda a, b: a+b, self.data,div.data))
    

def H():
    return Divisor([1]+[0]*N)

def E(i):
    data=[0]*(N+1)
    data[i]=1
    return Divisor(data)

def K():
    return Divisor([-3]+[1]*N)

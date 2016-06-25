
class BinomialTable:
    def __init__(self, maxsize):
        self.table=[ [0]*maxsize]
        self.table[0][0]=1
        while(len(self.table)<maxsize):
            newrow=[1]+map(lambda a,b:a+b, self.table[-1][1:], self.table[-1][:-1])
            self.table=self.table+[newrow]

    def binomial(self, a,b):
        if(a<len(self.table) and b<len(self.table)):
            return self.table[a][b]
        if(b>a):
            return 0
        if(b==0):
            return 1
        return self.binomial(a-1,b)+self.binomial(a-1,b-1)


if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser(description="Given two positive integers, returns the binomial",
                                     epilog="Returns (a choose b)")
    parser.add_argument('a', type=int, help='a positive integer')
    parser.add_argument('b', type=int, help='a positive integer')

    args = parser.parse_args()

    table=BinomialTable(10)
    print table.binomial(args.a,args.b)




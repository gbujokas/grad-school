import unittest
import binomialtable

class BinomialTableTest(unittest.TestCase):
    
    def setUp(self):
        self.table= binomialtable.BinomialTable(5)

    def test_binomial(self):
        testcases=[(0,0,1),
                   (0,1,0),
                   (2,1,2),
                   (2,2,1),
                   (2,3,0),
                   (4,2,6),
                   (7,2,21)]

        for a,b,res in testcases:
            self.assertEqual(self.table.binomial(a,b), res)




if __name__ == '__main__':
    unittest.main()

import unittest
from severi import TangencyIndex

def tangencyindexfromlist(elements):
    multiset=TangencyIndex()
    for elt in elements:
        multiset.add(elt)
    return multiset

#class TangencyIndexTest(unittest.TestCase):
#    def setUp(self):
#    def test_xxxxx(self):








if __name__ == '__main__':
    unittest.main()

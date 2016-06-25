
choose2 :: Int -> Int
choose2 n = quot (n*(n-1))  2

dim d m = (choose2 (d+2)) - 10*(choose2 (m+1))
genus d m = (choose2 (d-1)) - 10*(choose2 m)
residualIntersection :: Int -> Int -> Int
residualIntersection d m = 3*d - 10*m

info d m = [dim d m , genus d m, residualIntersection d m]
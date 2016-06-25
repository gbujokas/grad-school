loadPackage "VersalDeformations"
Ambient=QQ[x,y,z,w]
I=ideal(x*y,x*z,y*y,y*z)
degree I
genus I
N=normalMatrix(0,I)
F0=gens I
T1=cotangentCohomology1 (0,I)
T2=cotangentCohomology2 (0,I)
R0 = gens ker F0

(F,R)=firstOrderDeformations(F0,T1,R0)
(F,R,G,C)=versalDeformation(F0,T1,T2, Verbose=>2)
T=ring first G
numgens T
decompose ideal sum G
Def_0_1*R0+F0*Def_1_1

I2=minors(2,matrix {{x,y,z},{y,z,w}});
degree I2
genus I2
N=normalMatrix(0,I2)
cotangentCohomology1(0,I2)
cotangentCohomology2(0,I2)

J=ideal(x*z,y*z,z^2,x^3)
(F,R,G,C)=localHilbertScheme((gens J), Verbose=>2)
degree J
genus J
hilbertPolynomial J
T=ring first G
tangent=ideal sum G
decompose tangent
(gens J)
vars T
coefficientRing T

resol=resolution I
resol.dd
resol
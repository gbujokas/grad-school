--
R=QQ[X,Y,t, s1,s2,s3]
i1=ideal(X,Y)
i2=ideal(X,Y-s1*t)
i3=ideal(X-s2*t,Y)
i4=ideal(X-s3*t,Y-s3*t)

I=intersect(i1,i2,i3,i4)
I0=sub(I,{t=>0})


R=QQ[X,Y,t, a,b]
i1=ideal(X,Y)
i2=ideal(X,Y-(1-a)*t)
i3=ideal(X-(1-b)*t,Y)
i4=ideal(X-t,Y-t)

I=intersect(i1,i2,i3,i4)
I0=sub(I,{t=>0})
trim I0


R=QQ[X,Y,Z,t, a,b]
i1=ideal(X,Y,Z)
i2=ideal(X,Y-(1-a)*t,Z)
i3=ideal(X-(1-b)*t,Y,Z)
i4=ideal(X,Y, Z-t)

I=intersect(i1,i2,i3,i4)
I0=sub(I,{t=>0})
trim I0
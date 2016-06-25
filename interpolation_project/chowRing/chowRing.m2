R=QQ[n,d,mi,m];
S= R[h,e, z, f, hb, eb, fb,  Degrees=>{{1},{1},{1},{2},{1},{1},{2}}];
I=ideal(h^2-f,e^2+n*f,h*f,e*f,f^2, h*e, 
     hb^2-fb, eb^2+n*fb, hb*fb, eb*fb, hb*eb,
     z*h-z*hb, z*f-z*fb, z*e- z*eb, z^3-(3*h-e)*z^2+(3+n)*z*f, f*fb*z,
     f*fb+z^2*f) ;
Chow= S/I;

use Chow;

c1=3*hb-eb-z;
c2=(-z^2+(3+n)*fb);

td= 1+c1/2+ (c1*c1+c2)/12 + c1*c2/24 + (-c1^4+4*c1^2 * c2 +3 *c2^2)/720

c=d*hb-mi*eb - m*z;

L=1+c+ c^2/2 + c^3/6 + c^4/24;

td*L


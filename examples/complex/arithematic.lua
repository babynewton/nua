require 'libnua'
a = complex.cartesian(10,1)
print("a=",a)
ar = complex.cartesian(10,2)
print("ar=",ar)
b = a + ar
print("b=a+ar",b)
c = complex.cartesian(3,2)
print("c=", c)
d = b - c
print("d=b-c", d)
e = b * c
print("e=b*c", e)
f = b / c
print("f=b/c", f)

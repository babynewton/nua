require 'libnua'
a=complex.cartesian(10,4)
print("a=",a)
print("a.real=", complex.real(a))
print("a.imag=", complex.image(a))
print("a.mag=", complex.magnitude(a))
print("a.phase=", complex.phase(a))
a=complex.polar(10,3.14/4)
print("a.real=", complex.real(a))
print("a.imag=", complex.image(a))
print("a.mag=", complex.magnitude(a))
print("a.phase=", complex.phase(a))


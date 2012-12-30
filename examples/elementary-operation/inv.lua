require 'libnua'

a=matrix.new(3,3)
matrix.dump(a,1,0,0,0,0,3,0,2,0)
print("a[] is...")
print(a)
b=matrix.invert(a)
print("a^-1[] is...")
print(b)
c=b*a
print("a[]*a^-1[] is...")
print(c)

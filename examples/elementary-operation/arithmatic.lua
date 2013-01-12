require 'libnua'
a=matrix.new(3,3)
matrix.dump(a,1,2,3,4,5,6,7,8,9)
b=matrix.new(3,3)
matrix.dump(b,0,1,2,3,4,5,6,7,8)
print("a[] is...")
print(a)
print("b[] is...")
print(b)
c=a+b
print("c[]=a+b is...")
print(c)
d=a-b
print("d[]=a-b is...")
print(d)
print("-a[] is...")
print(-a)


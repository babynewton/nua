require 'libnua'
a=matrix.new(3,3)
matrix.dump(a,1,3,0,2,6,4,-1,0,2)
--det(a) should be -12
print(matrix.determinant(a))

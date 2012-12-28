require "libnua"

--Creating new matrix with a dimension of 3
local x = matrix.new(3,3)
--[[
--Initializing the matrix with values
--Matrix b is supposed to be...
--1, 2, 3
--4, 5, 6
--7, 8, 9
--]]
k=1
for i=1,3 do
	for j=1,3 do
		x[i][j]=k
		k=k+1
	end
end
print "x[] is..."
print(x)
--Creating new vector with a size of 3
local a = matrix.column(3)
--Initializing the vector with values
k=1
for i=1,3 do
	a[i][1]=k
	k=k+1
end
print "a[] is..."
print(a)
--It's a simple matrix operation
local b = x * a
--b is supposed to be [14, 32, 50]
print "b = x * a is..."
for i=1,3 do
	print (b[i][1])
end

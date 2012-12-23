require "libnua"

--Creating new matrix with a dimension of 3
local x = algebra.matrix(3,3)
--[[
--Initializing the matrix with values
--Matrix b is supposed to be...
--1, 2, 3
--4, 5, 6
--7, 8, 9
--]]
x:set(1,2,3,4,5,6,7,8,9)
--Creating new vector with a size of 3
local a = algebra.column(3)
--Initializing the vector with values
a:set(1,2,3)
--It's a simple matrix operation
local b = x * a
--b is supposed to be [14, 32, 56]
print (b)

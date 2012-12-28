require 'libnua'
a=matrix.new(3,3)
b=matrix.new(4,4)
c,e=a*b
if c ~= nil then
	print("c=",c)
else
	print("error=",e)
end

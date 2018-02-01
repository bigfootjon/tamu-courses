def sum(array)
	sum = 0
	array.each {|x| sum += x }
	return sum
end

puts(sum([1,2,3,4]))
puts(sum([]))

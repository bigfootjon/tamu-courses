def sum_to_n?(array, n)
	array.each {|x1|
		array.each {|x2|
			if x1 + x2 == n
				return true
			end
		}
	}
	return false
end

puts(sum_to_n?([], 15))
puts(sum_to_n?([1], 2))
puts(sum_to_n?([1], 4))
puts(sum_to_n?([1,3], 4))

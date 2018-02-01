def max_2_sum(array)
	m1 = 0
	m2 = 0
	array.each {|x|
		if x > m1
			m1 = x
		elsif x > m2
			m2 = x
		end
	}
	return m1 + m2
end

puts(max_2_sum([]))
puts(max_2_sum([1]))
puts(max_2_sum([6,2,5,4,1]))

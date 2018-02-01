def binary_multiple_of_4?(s)
	if s.length >= 2
		return (s[s.length-1] == "0" and s[s.length-2] == "0")
	else
		return s[0] == "0"
	end
end

puts(binary_multiple_of_4?("1"))
puts(binary_multiple_of_4?("10"))
puts(binary_multiple_of_4?("0"))
puts(binary_multiple_of_4?("00"))
puts(binary_multiple_of_4?("000"))
puts(binary_multiple_of_4?("100"))
puts(binary_multiple_of_4?("1000"))
puts(binary_multiple_of_4?("10100"))
puts(binary_multiple_of_4?("11111100"))

def palindrome?(string)
	string = string.downcase().gsub(/\W/, '')
	return string == string.reverse()
end

puts("#{palindrome?("A man, a plan, a canal -- Panama")} == T")
puts("#{palindrome?("Madam, I'm Adam!")} == T")
puts("#{palindrome?("Abracadabra")} == F")


def starts_with_consonant?(s)
	i = s.index(/a|e|i|o|u/)
	return i != 0
end

puts(starts_with_consonant?(""))
puts(starts_with_consonant?("test"))
puts(starts_with_consonant?("aloha"))

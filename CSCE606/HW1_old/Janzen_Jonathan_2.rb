def count_words(string)
	words = string.downcase().split(/\W/)
	dict = Hash.new()
	words.each {|word|
		if word == ""
			next
		end
		if dict.key?(word)
			dict[word] = dict[word] + 1
		else
			dict[word] = 1
		end
	}
	return dict
end

puts(count_words("A man, a plan, a canal -- Panama"))
puts(count_words("Doo bee doo bee doo"))


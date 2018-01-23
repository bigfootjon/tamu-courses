def alpha_order(word)
	# convert to char array, sort, then convert back to string
	return word.chars().sort().join()
end

def combine_anagrams(words)
	tree = Hash.new()
	words.each { |word| 
		alpha = alpha_order(word)
		if tree.key?(alpha)
			tree[alpha] << word
		else
			tree[alpha] = [word]
		end
	}
	return tree.values()
end

print(combine_anagrams(['cars', 'for', 'potatoes', 'racs', 'four','scar', 'creams', 'scream']))
puts()


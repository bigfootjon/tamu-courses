class Dessert
	def initialize(name, calories)
		@name = name
		@calories = calories
	end

	def healthy?
		return @calories < 200
	end

	def delicious?
		return true
	end
end


class JellyBean < Dessert
	def initialize(name, calories, flavor)
		@name = name
		@calories = calories
		@flavor = flavor
	end
	
	def flavor=(flavor)
		@flavor = flavor
	end
	
	def flavor()
		return @flavor
	end

	def delicious?
		return flavor != "black licorice"
	end
end

class BookInStock
	def initialize(isbn, price)
		self.isbn = isbn
		self.price = price
	end
	
	def isbn()
		return @isbn
	end

	def isbn=(value)
		raise ArgumentError unless (value.kind_of?(String) and value.length > 0)
		@isbn = value
	end

	def price()
		return @price
	end

	def price=(value)
		raise ArgumentError unless (value.kind_of?(Float) and value > 0)
		@price = value
	end

	def price_as_string()
		return "$%.2f" % @price
	end
end

puts(BookInStock.new("1234-12354", 123.45678).price_as_string())

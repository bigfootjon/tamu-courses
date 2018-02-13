# When done, submit this entire file to the autograder.

# Part 1

def sum arr
  sum = 0
  arr.each {|x| sum += x }
  return sum
end

def max_2_sum arr
  m1 = nil
  m2 = nil
  arr.each {|x|
    if m1 == nil or x > m1
      m1 = x
    elsif m2 == nil or x > m2
      m2 = x
    end
  }
  if m1 == nil or m2 == nil
    if m1 != nil
      return m1
    elsif m2 != nil
      return m2
    else
      return 0
    end
  else
    return m1 + m2
  end
end

def sum_to_n? arr, n
  arr.each_with_index {|x1, i1|
    arr.each_with_index {|x2, i2|
      if i1 == i2
        next
      end
      if x1 + x2 == n
        return true
      end
    }
  }
  return false
end

# Part 2

def hello(name)
  return "Hello, #{name}"
end

def starts_with_consonant? s
  return /^[bcdfghjklmnpqrstvwxyz]/.match(s.downcase) != nil
end

def binary_multiple_of_4? s
  if s.downcase.index(/[^10]/) != nil
    return false
  end
  if s.length >= 2
    return (s[s.length-1] == "0" and s[s.length-2] == "0")
  else
    return s[0] == "0"
  end
end

# Part 3

class BookInStock
  def initialize(isbn, price)
    self.isbn = isbn
    self.price = Float(price)
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

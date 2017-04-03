var a = 0;
var b = a;
a = 12;

while (b < a) {
  if (b < 4 || b == 4) {
    print b;
    print "\n";
  } else {
    print a + "\n";
  }
  b = b + 1;
}

print "done\n";

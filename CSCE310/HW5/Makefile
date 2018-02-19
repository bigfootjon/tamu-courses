run: run1

%.class: %.java
	javac $<

run2: Problem2.class
	java -cp ".:./mysql.jar" Problem2

run1: Problem1.class
	java Problem1

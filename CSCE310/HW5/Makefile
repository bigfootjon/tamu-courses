MYSQL_USER=jonjanzen
MYSQL_PASS=dbpass

run: run4

%.class: %.java
	javac $<

run1: Problem1.class
	java Problem1

run2: Problem2.class
	java -cp ".:./mysql.jar" Problem2 ${MYSQL_USER} ${MYSQL_PASS}

run3: Problem3.class
	java -cp ".:./mysql.jar" Problem3 ${MYSQL_USER} ${MYSQL_PASS}

run4: ClassifyPatents.class Classifier.class
	java -cp ".:./mysql.jar" ClassifyPatents ${MYSQL_USER} ${MYSQL_PASS}
	

clean:
	rm -f *.class


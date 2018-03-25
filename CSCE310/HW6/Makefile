MYSQL_USER=jonjanzen
MYSQL_PASS=dbpass

run: run7

%.class: %.java
	javac -cp ".:./bson-3.0.4.jar:./mongodb-driver-3.0.4.jar:./mongodb-driver-core-3.0.4.jar" $<

run7: Problem7.class AnalyzePatentDates.class CreatePatentCollection.class
	java Problem7

clean:
	rm -f *.class *.log


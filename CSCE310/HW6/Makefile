MYSQL_USER=jonjanzen
MYSQL_PASS=dbpass
PR4_DIR=patentClassifier

run: runA

%.class: %.java
	javac -cp ".:./bson-3.0.4.jar:./mongodb-driver-3.0.4.jar:./mongodb-driver-core-3.0.4.jar" $<

runC: CreatePatentCollection.class
	java -cp ".:./bson-3.0.4.jar:./mongodb-driver-3.0.4.jar:./mongodb-driver-core-3.0.4.jar" CreatePatentCollection

runA: AnalyzePatentDates.class
	java -cp ".:./bson-3.0.4.jar:./mongodb-driver-3.0.4.jar:./mongodb-driver-core-3.0.4.jar" AnalyzePatentDates

run4: ${PR4_DIR}/DocWord.class ${PR4_DIR}/PatentData.class ${PR4_DIR}/Classifier.class ${PR4_DIR}/ClassifyPatents.class
	java -cp ".:./mysql.jar" ${PR4_DIR}/ClassifyPatents ${MYSQL_USER} ${MYSQL_PASS}

clean:
	rm -f *.class ${PR4_DIR}/*.class *.log


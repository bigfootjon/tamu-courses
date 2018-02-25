MYSQL_USER=jonjanzen
MYSQL_PASS=dbpass
PR4_DIR=patentClassifier

run: run4

%.class: %.java
	javac $<

run1: Problem1.class
	java Problem1

run2: Problem2.class
	java -cp ".:./mysql.jar" Problem2 ${MYSQL_USER} ${MYSQL_PASS}

run3: Problem3.class
	java -cp ".:./mysql.jar" Problem3 ${MYSQL_USER} ${MYSQL_PASS}

run4: ${PR4_DIR}/DocWord.class ${PR4_DIR}/PatentData.class ${PR4_DIR}/Classifier.class ${PR4_DIR}/ClassifyPatents.class
	java -cp ".:./mysql.jar" ${PR4_DIR}/ClassifyPatents ${MYSQL_USER} ${MYSQL_PASS}

clean:
	rm -f *.class ${PR4_DIR}/*.class *.log


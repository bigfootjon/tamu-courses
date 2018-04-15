package com.jonathanjanzen.hw8;

import simpledb.parse.QueryData;
import simpledb.query.FieldNameExpression;
import simpledb.query.Predicate;
import simpledb.query.Term;
import simpledb.server.SimpleDB;
import simpledb.tx.Transaction;

import java.util.ArrayList;

public class Pr5 {
    public static void main(String[] args) {

        //TODO WRONG WRONG WRONG SEE SLIDE 10 of QUERY PLANNING

        // QUERY:
        //   SELECT sname, dname, grade
        //   FROM STUDENT, DEPT, ENROLL, SECTION
        //   WHERE SId = StudentId AND SectId = SectionId and DId = MajorId;

        // Slides from Query Processing, Use SimpleDb.{Plan, Scan}

        SimpleDB.init("studentdb");
        Transaction tx = new Transaction();

        // --- SELECT CLAUSE ---
        ArrayList<String> fields = new ArrayList<>();
        fields.add("sname");
        fields.add("dname");
        fields.add("grade");
        // --- END SELECT CLAUSE ---

        // --- FROM CLAUSE ---
        ArrayList<String> tables = new ArrayList<>();
        tables.add("STUDENT");
        tables.add("DEPT");
        tables.add("ENROLL");
        tables.add("SECTION");
        // --- END FROM CLAUSE ---

        // --- WHERE CLAUSE ---
        Predicate predicate = new Predicate(new Term(new FieldNameExpression("SId"), new FieldNameExpression("StudentId")));
        Predicate predicateSection = new Predicate(new Term(new FieldNameExpression("SectId"), new FieldNameExpression("SectionId")));
        Predicate predicateMajor = new Predicate(new Term(new FieldNameExpression("DId"), new FieldNameExpression("MajorId")));

        predicate.conjoinWith(predicateSection);
        predicate.conjoinWith(predicateMajor);
        // --- END WHERE CLAUSE ---

        QueryData query = new QueryData(fields, tables, predicate);
    }
}

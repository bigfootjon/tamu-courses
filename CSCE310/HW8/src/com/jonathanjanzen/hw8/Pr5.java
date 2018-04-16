package com.jonathanjanzen.hw8;

import simpledb.query.*;
import simpledb.server.SimpleDB;
import simpledb.tx.Transaction;

import java.util.ArrayList;

public class Pr5 {
    public static void main(String[] args) {

        // QUERY:
        //   SELECT sname, dname, grade
        //   FROM student, dept, enroll, section
        //   WHERE sid = studentid AND sectid = sectionid and did = majorid;

        // Slides from Query Processing, Use SimpleDb.{Plan, Scan}

        SimpleDB.init("studentdb");
        Transaction tx = new Transaction();

        // --- FROM Clause ---
        Plan tableStudent = new TablePlan("student", tx);
        Plan tableDept = new TablePlan("dept", tx);
        Plan tableEnroll = new TablePlan("enroll", tx);
        Plan tableSection = new TablePlan("section", tx);

        Plan p = new ProductPlan(tableStudent, tableDept);
        p = new ProductPlan(p, tableEnroll);
        p = new ProductPlan(p, tableSection);
        // --- End FROM Clause ---

        // --- WHERE Clause ---
        Predicate predicateStudent = new Predicate(new Term(new FieldNameExpression("sid"), new FieldNameExpression("studentid")));
        Predicate predicateSection = new Predicate(new Term(new FieldNameExpression("sectid"), new FieldNameExpression("sectionid")));
        Predicate predicateMajor = new Predicate(new Term(new FieldNameExpression("did"), new FieldNameExpression("majorid")));

        p = new SelectPlan(p, predicateStudent);
        p = new SelectPlan(p, predicateSection);
        p = new SelectPlan(p, predicateMajor);
        // --- End WHERE Clause ---

        // --- SELECT Clause ---
        ArrayList<String> fields = new ArrayList<>();
        fields.add("sname");
        fields.add("dname");
        fields.add("grade");

        p = new ProjectPlan(p, fields);
        // --- End SELECT Clause ---

        Scan s = p.open();
        System.out.println("sname\tdname\tgrade");
        while (s.next()) {
            String sname = s.getString("sname");
            String dname = s.getString("dname");
            String grade = s.getString("grade");
            System.out.println(sname + "\t\t" + dname + "\t" + grade);
        }
    }
}

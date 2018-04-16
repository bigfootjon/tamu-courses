package com.jonathanjanzen.hw8;

import simpledb.query.*;
import simpledb.server.SimpleDB;
import simpledb.tx.Transaction;

import java.util.ArrayList;

public class DifferenceTest {
    public static void main(String[] args) throws Exception {
        SimpleDB.init("studentdb");
        Transaction tx = new Transaction();

        Plan tableStudent = new TablePlan("student", tx);
        ArrayList<String> projectionFields = new ArrayList<>();
        projectionFields.add("sid");
        projectionFields.add("sname");
        tableStudent = new ProjectPlan(tableStudent, projectionFields);

        Predicate pred = new Predicate(new Term(new FieldNameExpression("sid"), new ConstantExpression(new IntConstant(1))));
        Plan singleStudent = new SelectPlan(tableStudent, pred);

        Plan bigger = new DifferencePlan(tableStudent, singleStudent);
        Scan biggerScan = bigger.open();
        System.out.println(" --- Scan where LHS > RHS --- ");
        System.out.println("sid\tsname");
        while (biggerScan.next()) {
            int sid = biggerScan.getInt("sid");
            String sname = biggerScan.getString("sname");
            System.out.println(sid + "\t" + sname);
        }
        System.out.println(" --- END: Expect all except sid=1 --- ");
        System.out.println(); // Spacing line
        Plan smaller = new DifferencePlan(tableStudent, bigger);
        Scan smallerScan = smaller.open();
        System.out.println(" --- Scan where LHS < RHS --- ");
        System.out.println("sid\tsname");
        while (smallerScan.next()) {
            int sid = smallerScan.getInt("sid");
            String sname = smallerScan.getString("sname");
            System.out.println(sid + "\t" + sname);
        }
        System.out.println(" --- END: Expect only sid=1 --- ");
        System.out.println(); // Spacing line
        Plan equal = new DifferencePlan(tableStudent, tableStudent);
        Scan equalScan = equal.open();
        System.out.println(" --- Scan where LHS = RHS --- ");
        System.out.println("sid\tsname");
        while (equalScan.next()) {
            int sid = equalScan.getInt("sid");
            String sname = equalScan.getString("sname");
            System.out.println(sid + "\t" + sname);
        }
        System.out.println(" --- END: Expect null set --- ");
    }
}

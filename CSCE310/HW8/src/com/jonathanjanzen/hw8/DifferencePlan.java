package com.jonathanjanzen.hw8;

import simpledb.query.Plan;
import simpledb.query.Scan;
import simpledb.record.Schema;

import java.util.Collection;

public class DifferencePlan implements Plan {

    private final Plan p1;
    private final Plan p2;
    private Schema schema;

    public DifferencePlan(Plan p1, Plan p2) throws Exception {
        // begin input validation
        Schema s1 = p1.schema();
        Collection<String> s1f = s1.fields();
        Schema s2 = p2.schema();
        Collection<String> s2f = s2.fields();
        if (s1f.size() != s2f.size()) {
            throw new Exception("Plans schemas do not match");
        }
        for (String name : s1f) {
            if (!s2.hasField(name) || s1.type(name) != s2.type(name)) {
                throw new Exception("Plans schemas do not match");
            }
        }
        // end input validation
        schema = s1;
        this.p1 = p1;
        this.p2 = p2;
    }

    @Override
    public Scan open() {
        return new DifferenceScan(p1.open(), p2.open(), schema);
    }

    @Override
    public int blocksAccessed() {
        return p1.blocksAccessed() + p2.blocksAccessed();
    }

    @Override
    public int recordsOutput() {
        return Math.min(p1.recordsOutput(), p2.recordsOutput());
    }

    @Override
    public int distinctValues(String fldname) {
        return Math.min(p1.distinctValues(fldname), p2.distinctValues(fldname));
    }

    @Override
    public Schema schema() {
        return schema;
    }
}

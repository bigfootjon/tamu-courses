package com.jonathanjanzen.hw8;

import simpledb.query.Constant;
import simpledb.query.Scan;
import simpledb.record.Schema;

import java.util.Collection;

public class DifferenceScan implements Scan {
    private final Scan s1;
    private final Scan s2;
    private final Collection<String> fields;

    DifferenceScan(Scan s1, Scan s2, Schema schema) {
        this.s1 = s1;
        this.s2 = s2;
        this.fields = schema.fields();
    }

    @Override
    public void beforeFirst() {
        s1.beforeFirst();
        s2.beforeFirst();
    }

    @Override
    public boolean next() {
        while (s1.next()) {
            s2.beforeFirst();
            boolean identical = false;
            while (s2.next()) {
                if (identicalTuples()) {
                    identical = true;
                    break;
                }
            }
            if (!identical) {
                return true;
            }

        }
        return false;
    }

    private boolean identicalTuples() {
        for (String field : fields) {
            if (!s1.getVal(field).equals(s2.getVal(field))) {
                return false;
            }
        }
        return true;
    }

    @Override
    public void close() {
        s1.close();
        s2.close();
    }

    @Override
    public Constant getVal(String fldname) {
        return s1.getVal(fldname);
    }

    @Override
    public int getInt(String fldname) {
        return s1.getInt(fldname);
    }

    @Override
    public String getString(String fldname) {
        return s1.getString(fldname);
    }

    @Override
    public boolean hasField(String fldname) {
        return s1.hasField(fldname);
    }
}

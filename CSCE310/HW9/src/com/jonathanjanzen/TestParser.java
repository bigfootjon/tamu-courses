package com.jonathanjanzen;

import simpledb.parse.DeleteData;
import simpledb.parse.Parser;

public class TestParser {
    public static void main(String[] args) {
        Parser parser = new Parser("delete from xyz where a = b and c = 0");
        DeleteData data = parser.delete();
        System.out.println("table: " + data.tableName());
        System.out.println("Pred: " + data.pred().toString());
    }
}

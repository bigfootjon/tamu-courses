package simpledb.query;

import java.util.Collection;
import java.util.Iterator;

import simpledb.record.Schema;

/**
 * The scan class corresponding to the <i>intersect</i> relational
 * algebra operator.
 * @author Edward Sciore and Ronnie Ward
 */
public class IntersectScan implements Scan {
   private Scan s1, s2;
   private Schema sch1, sch2;
   
   /**
    * Creates a Intersect scan from the underlying scans.
    * @param s1 the LHS scan
    * @param s2 the RHS scan
    */
   public IntersectScan(Scan s1, Scan s2, Schema sch1, Schema sch2) {
	   //assume the schemas are compatible and that the Scan is being initiated from an IntersectPlan--rgw
	  this.s1 = s1;
      this.s2 = s2;
      this.sch1 = sch1;
      this.sch2 = sch2;
   }
   
   /**
    * Positions the scan before its first record.
    * In other words, the LHS scan is positioned at 
    * its first record, and the RHS scan
    * is positioned before its first record.
    * @see simpledb.query.Scan#beforeFirst()
    */
   public void beforeFirst() {
      s1.beforeFirst();
      //s1.next();
      s2.beforeFirst();
   }
   
   /**
    * Moves the s1 scan to the next record where all fields of both scans have the same values.
    * The method is not very cost efficient. It may scan all of s2 for each record in s1.
    * It moves to the next LHS record and the first RHS record that have matching values.
    * If there are no more LHS records, the method returns false.
    * @see simpledb.query.Scan#next()
    */
   public boolean next() {
	  Collection<String> col1 = sch1.fields();
	  Collection<String> col2 = sch2.fields();
      while(s1.next()){//hunt for a matching s1 and s2 record
    	  s2.beforeFirst(); //reposition s2 scan to look for a match for the this s1 record
    	  while(s2.next()){
    		  if(match(s1, s2, col1, col2))
    			  return true;
    	  }
    	  //no s2 records match so move to next s1 record
      }
      return false;
   }	  
//         return true;
//      else {
//         s2.beforeFirst();
//         return s2.next() && s1.next();
   /**
    * checks to see if two records underlying scans have matching values.
    */
   private boolean match(Scan s1, Scan s2, Collection<String> c1, Collection<String> c2){
	  Iterator<String> i2 = c2.iterator();
	  for (String str1: c1){
		  String str2 = i2.next();
		  Constant v1 = s1.getVal(str1);	//order assumed
		  Constant v2 = s2.getVal(str2);
		  if(0!=v1.compareTo(v2))
			  return false;					//records do not match  
	  }
	  return true; //records match
   }
   /**
    * Closes both underlying scans.
    * @see simpledb.query.Scan#close()
    */
   public void close() {
      s1.close();
      s2.close();
   }
   
   /** 
    * Returns the value of the specified field.
    * The value is obtained from the s1 scan
    * @see simpledb.query.Scan#getVal(java.lang.String)
    */
   public Constant getVal(String fldname) {
	   return s1.getVal(fldname);
 /*     if (s1.hasField(fldname))
         return s1.getVal(fldname);
      else
         return s2.getVal(fldname);
 */  }
   
   /** 
    * Returns the integer value of the specified field.
    * The value is obtained from the s1 scan
    * @see simpledb.query.Scan#getInt(java.lang.String)
    */
   public int getInt(String fldname) {
	  return s1.getInt(fldname);
/*      if (s1.hasField(fldname))
         return s1.getInt(fldname);
      else
         return s2.getInt(fldname);
*/   }
   
   /** 
    * Returns the string value of the specified field.
    * The value is obtained from the s1 scan
    * @see simpledb.query.Scan#getString(java.lang.String)
    */
   public String getString(String fldname) {
	   return s1.getString(fldname);
/*      if (s1.hasField(fldname))
         return s1.getString(fldname);
      else
         return s2.getString(fldname);
 */
   }
   
   /**
    * Returns true if the specified field is in the s1 scan.
    * @see simpledb.query.Scan#hasField(java.lang.String)
    */
   public boolean hasField(String fldname) {
      return s1.hasField(fldname);// || s2.hasField(fldname);
   }
}

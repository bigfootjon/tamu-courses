package simpledb.query;

import java.util.Collection;
import java.util.Iterator;
import simpledb.record.Schema;

/** The Plan class corresponding to the <i>intersect</i>
  * relational algebra operator.
  * @author Edward Sciore and Ronnie Ward
  */
public class IntersectPlan implements Plan {
   private Plan p1, p2;
   private Schema schema = new Schema();
   
   /**
    * Creates a new Intersect node in the query tree,
    * having the two specified subqueries.
    * @param p1 the left-hand subquery
    * @param p2 the right-hand subquery
    */
   public IntersectPlan(Plan p1, Plan p2) {
	  //make sure the subqueries are union compatible -- rgw
	  Collection<String> c1 = p1.schema().fields();	
	  Collection<String> c2 = p2.schema().fields();
	  if(c1.size() != c2.size())						//same number of elements?
		  throw new BadSemanticsException();
	  Iterator<String> i2 = c2.iterator();
	  for(String str1: c1){
		  String str2 = i2.next();						//I assume there is an order to the elements
		  if(p1.schema().type(str1) != p2.schema().type(str2)) //same type of element
			  throw new BadSemanticsException();
	  }
      this.p1 = p1;
      this.p2 = p2;
      schema.addAll(p1.schema());		//the output table will have the schema of Plan p1
      //schema.addAll(p2.schema());
   }
   
   /**
    * Creates a Intersect scan for this query.
    * @see simpledb.query.Plan#open()
    */
   public Scan open() {
      Scan s1 = p1.open();
      Scan s2 = p2.open();
      return new IntersectScan(s1, s2, p1.schema(), p2.schema());
   }
   
   /**
    * Estimates the number of block accesses in the Intersection.
    * The formula is:
    * <pre> B(Intersect(p1,p2)) = B(p1) + R(p1)*B(p2) </pre>
    * @see simpledb.query.Plan#blocksAccessed()
    */
   public int blocksAccessed() {
      return p1.blocksAccessed() + (p1.recordsOutput() * p2.blocksAccessed()); 
   }
   
   /**
    * Estimates the number of output records in the product.
    * The formula is:
    * <pre> R(intersect(p1,p2)) = R(p1) </pre>
    * @see simpledb.query.Plan#recordsOutput()
    */
   public int recordsOutput() {
      return p1.recordsOutput();// * p2.recordsOutput();	//rgw
   }
   
   /**
    * Estimates the distinct number of field values in the intersection.
    * Since the intersection does not increase or decrease field values,
    * the estimate is the same as in the appropriate underlying query.
    * @see simpledb.query.Plan#distinctValues(java.lang.String)
    */
   public int distinctValues(String fldname) {
      if (p1.schema().hasField(fldname))
         return p1.distinctValues(fldname);
      else
         return p2.distinctValues(fldname);
   }
   
   /**
    * Returns the schema of the intersection,
    * which is the schema of the underlying p1 queries.
    * @see simpledb.query.Plan#schema()
    */
   public Schema schema() {
      return schema;
   }
}

package mongodb;
import org.bson.Document;
import com.mongodb.MongoClient;
import com.mongodb.MongoException;
import com.mongodb.client.FindIterable;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.model.Projections;
//helpful code examples: https://www.programcreek.com/java-api-examples/?api=com.mongodb.client.FindIterable
//
//This program illustrates processing fields in a patent document stored in a MongoDB collection.
//Each patent has the following JSON fields: {"patNum":"D238414","iDate":"January 13, 1976","title":"","abstract":"","inventors":"","assignee":"","familyID":"","applNum":"","dateFiled":"","docID":"","pubDate":"","USclass":"D10/50","references":"","claims":"","examiner":"","legalfirm":"","summary":"","description":""}
//All field values are presented as strings, but might be better stored in the database as different 
//types to facilitate comparisons (e.g. DATE type)
//The field "inventors" may have multiple subfields representing individual inventors, but the data is presented as a single String. It needs to be further parsed. 
//The fields "references" and "claims" may have subfields, and if so they are presented as JSON subfields named ref# and claim# where # is a number. E.g. ref14 or claim7
//Text fields like "abstract", "claims", "summary" and "description" make be large text strings (thousands of characters).

//Author: Ronnie Ward
//
public class AnalyzePatentDates {

	public static void main(String[] args) throws Exception {
		try {
			MongoClient mongoClient = new MongoClient( "localhost" , 27017 );

			MongoCollection<Document> coll = null;
			MongoDatabase database = mongoClient.getDatabase("patentdb");
			if(database!=null) {
				
				System.out.println("Connect to Database Successful");
				coll = database.getCollection("patent1000");
		        if(coll!=null)
		        	System.out.println("Select Collection Successful");
		        else System.out.println("Collection NOT found!");
			}
			else System.out.println("Database NOT found!");

			FindIterable<Document> docs = coll.find().projection(Projections.include("indx", "dateFiled"));
			if(docs != null) {
				System.out.println("Index\tdateFiled");
				for (Document doc : docs) {
					int indx = doc.getInteger("indx");
		            String df = doc.getString("dateFiled");
		            System.out.println(indx+"\t"+df);
		        }
			}
 	    	else System.out.println("First document NOT found");
 	    		    	
		} catch (MongoException e) {
			e.printStackTrace();
 		} finally {
 			
 		}
	}
}

package mongodb;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import org.bson.Document;

import com.mongodb.DB;
import com.mongodb.DBCollection;
import com.mongodb.MongoClient;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
///http://mongodb.github.io/mongo-java-driver/3.6/driver/getting-started/quick-start/
public class CreatePatentCollection {

	public static void main(String[] args) {
		try{
			ObjectInputStream objectinputstream = null;
			ArrayList<String> patentList = null;

			System.out.println("Enter patent input file name: ");
            Scanner input = new Scanner(System.in);
            String inputFile = input.nextLine().toLowerCase();
            int i = inputFile.indexOf(".ser");
            if(-1 != i)
             	inputFile = inputFile.substring(0, i);
 			FileInputStream streamIn = new FileInputStream(inputFile+".ser");//filename.ser");//
 		    objectinputstream = new ObjectInputStream(streamIn);
 	    	patentList  = (ArrayList<String>) objectinputstream.readObject();
 	    	List<Document> documents = null;
 	    	if (patentList != null){
 	    		System.out.println("Number of patents read: "+patentList.size());
 	    		documents = new ArrayList<Document>();
 	    		int indx = 0;
 	    		for (String jsonStr: patentList) {
 	    			//add an attribute "indx",x
 	    			int j = jsonStr.indexOf("{");
 	    			String js = "{"+"\"indx\":"+indx+","+jsonStr.substring(j+1);
 	    			indx++;//System.out.println(js);
 	    			documents.add(Document.parse(js));
 	    		}
 	    	}
			MongoClient mongoClient = new MongoClient( "localhost");// 27017 );
			MongoCollection<Document> coll = null;
			MongoDatabase database = mongoClient.getDatabase("patentdb");
			if(database!=null) {
				System.out.println("Connect to Database Successful");
				System.out.println("Enter name of collection: ");
				inputFile = input.nextLine().toLowerCase();	//e.g. patent1000
				coll = database.getCollection(inputFile);
		        if(coll!=null){
		        	System.out.println(inputFile+" Collection Selected Successful");
		        	coll.insertMany(documents);
		        	System.out.println("Patents added: "+coll.count());
		        	Document myDoc = coll.find().first();
		 	    	if(myDoc !=null)
		 	    		System.out.println(myDoc.toJson());
		 	    	else System.out.println("First document NOT found");
		        }
		        else System.out.println("Collection NOT found!");
			}
			else System.out.println("Database NOT found!");	    	

 		} catch (Exception e) {
 		    e.printStackTrace();
 		} 	
	}
}

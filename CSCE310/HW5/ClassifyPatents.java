package patentClassifier;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;

//
// This program classifies patents as a database invention, or an invention of something else.
// In this first version, we consider the words (tokens) in the title.

// Each patent has the following JSON fields: {"patNum":"D238414","iDate":"January 13, 1976","title":"","abstract":"","inventors":"","assignee":"","familyID":"","applNum":"","dateFiled":"","docID":"","pubDate":"","USclass":"D10/50","references":"","claims":"","examiner":"","legalfirm":"","summary":"","description":""}
// All field values are presented as strings, but might be better stored in the database as different 
// types to facilitate comparisons (e.g. DATE type)
// The field "inventors" may have multiple subfields representing individual inventors, but the data is presented as a single String. It needs to be further parsed. 
// The fields "references" and "claims" may have subfields, and if so they are presented as JSON subfields named “ref#” and “claim#” where # is a number. E.g. ref14 or claim7
// Text fields like "abstract", "claims", "summary" and "description" make be large text strings (thousands of characters).

// Author: Ronnie Ward
//
public class ClassifyPatents {
	
	public static void main(String[] args) throws Exception {
		Classifier c = new Classifier(pdf);
		
		//read index of desired start patent	
		while(true){
	        	System.out.println("Enter patent start number: ");
	        	Scanner input = new Scanner(System.in);
	        	String inputLine = input.nextLine();
	        	int pn = Integer.parseInt(inputLine.trim());
	        	
	        	for (int i = pn; i < 1000; i++){
			        String patent = pdf.getPatent(i);
			        double pr = c.classify(patent);
			        PatentParser pp = new PatentParser(patent);
			        System.out.println("Patent index:"+i+"\t"+"Class: "+pr+"\t"+pp.findFieldValue("title"));
			        inputLine = input.nextLine();
			        if(inputLine.toLowerCase().contains("exit")) 
			        	break;   
	        	}
		}
	}
}

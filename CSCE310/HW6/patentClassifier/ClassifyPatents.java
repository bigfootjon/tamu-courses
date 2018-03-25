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

// This program classifies patents as a database invention, or an invention of something else.
// In this first version, we consider the words (tokens) in the title.

// Author: Ronnie Ward
public class ClassifyPatents {

	public static void main(String[] args) throws Exception {
		if (args.length != 2) {
			System.out.println("Please supply an username and password as args");
			return;
		}
		
		//read patent data
		PatentData pdf = new PatentData(args[0], args[1]);
		//train classifier
		Classifier c = new Classifier(pdf);
		
		//read index of desired start patent	
		while(true){
			System.out.print("Enter patent start number: ");
			Scanner input = new Scanner(System.in);
			String inputLine = input.nextLine();
			int pn = Integer.parseInt(inputLine.trim());
			
			for (int i = pn; i < 1000; i++){
				String title = pdf.getPatentField(i, "title");
				double pr = c.classify(title);
				System.out.println("Patent index:"+i+"\t"+"Class: "+pr+"\t"+title);
				inputLine = input.nextLine();
				if(inputLine.toLowerCase().contains("exit"))
					break;
			}
		}
	}
}

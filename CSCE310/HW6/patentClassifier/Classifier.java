package patentClassifier;

//This class classifies patents as a database invention, or an invention of something else using Paul Grahams spam v ham method
//In this first version, we consider the words (tokens) in the title.
//Author: Ronnie Ward

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;
import java.util.Comparator;
import java.util.Collections;

public class Classifier {
	int[] knownDByes = {2,3,4,5,6,7,8,12,13,14,17,18,19,20,21,23,24,27,28,29,30,31,34,36,37,38,39,41,46,50};
	int[] knownDBno = {0,1,9,10,11,15,16,22,25,26,32,33,35,40,42,43,44,45,47,48,49};
	double patYesCnt = knownDByes.length;
	double patNoCnt = knownDBno.length;
	HashSet<String> hset = new HashSet<String>();
	HashMap<String, DocWord> dict = new HashMap<String, DocWord>();//dictionary from training set
	
	public Classifier(PatentData pdf) throws Exception {
		try {
			BufferedReader in = new BufferedReader(new FileReader("stopwords.txt"));
			String str;
			while ((str = in.readLine()) != null) {
				hset.add(str.toLowerCase().trim());
			}
			in.close();
		} catch (IOException e) {
			System.out.println("File Read Error");
		}
		//train the classifier
		for (int yesDB: knownDByes)
			train(pdf.getPatentField(yesDB, "title"),true);
		System.out.println("YesWord Dictionary size: "+dict.size());
		for (int noDB: knownDBno)
			train(pdf.getPatentField(noDB, "title"),false);
		System.out.println("Total Dictionary size: "+dict.size());
		
		//compute word probabilities
		Set<String> keys = dict.keySet();
		for(String k: keys) {
			DocWord entry = dict.get(k);
			entry.yesFrac = entry.yesCnt/patYesCnt;	//avg freq per doc type
			entry.noFrac = entry.noCnt/patNoCnt;
			entry.yesProb = entry.yesFrac/(entry.yesFrac+entry.noFrac);
			//if (Float.isNaN(entry.yesProb)) throw new Exception();
			if (entry.yesProb < 0.01) entry.yesProb = 0.01D;
			else if (entry.yesProb > 0.99) entry.yesProb= 0.99D;
			entry.noProb = 1.0D - entry.yesProb;
			
			dict.replace(k, entry);
		}

		// BEGIN MODIFICATIONS
		ArrayList<DocWord> words = new ArrayList<DocWord>(dict.values());
		Collections.sort(words, new Comparator<DocWord>() {
			@Override
			public int compare(DocWord left, DocWord right) {
				return (int)(left.yesProb - right.yesProb);
			}
		});
		words = new ArrayList<DocWord>(words.subList(0, 5));
		dict.clear();
		for (DocWord elem : words) {
			dict.put(elem.word, elem);
		}
		// END MODIFICATIONS

	}
	public void train(String title, boolean DBinvention) throws IOException{
		String[] tokens = splitPatent(title);
		for (int i = 0; i < tokens.length; i++) {
			if (hset.contains(tokens[i])) //forget stop words
				continue;
			else processToken(tokens[i],DBinvention);
		}
		return;
	}
	private void processToken(String token, boolean patType) {
		
		if (!dict.containsKey(token)) {
			DocWord entry = new DocWord();
			entry.word = token;
			entry.yesCnt = 0;
			entry.noCnt = 0;
			dict.put(token, entry);
		}
		DocWord entry = dict.get(token);
		if (patType==true)
			entry.yesCnt++;
		else entry.noCnt++;
		dict.replace(token, entry);
	}
	public double classify(String title) throws Exception {
		HashSet<String> tset = new HashSet<String>();
		ArrayList<DocWord> words = new ArrayList<DocWord>();//words in new patent we are classifying
		String[] tokens = splitPatent(title);
		for(int i = 0; i < tokens.length; i++) {
			if (dict.containsKey(tokens[i]) && !tset.contains(tokens[i])) {
				//the token is in the dictionary and this is 1st time we have seen it in the patent
				tset.add(tokens[i]); //remember that we have seen this word
				words.add(dict.get(tokens[i]));
			}
		}
		System.out.println("Patent word count: "+words.size());
		//determine yes or no according to: http://www.paulgraham.com/naivebayes.html
		double yesProduct = 1.0D;
		double noProduct = 1.0D;
		for (DocWord dw: words) {
			yesProduct *= dw.yesProb;
			noProduct *= dw.noProb;
		}
		if (Double.isNaN(yesProduct)) throw new Exception();
		if (Double.isNaN(noProduct)) throw new Exception();
		double yesProb = yesProduct / (yesProduct + noProduct);
		if (Double.isNaN(yesProb)) throw new Exception();
		return yesProb;
	}
	
	private String[] splitPatent(String title) throws IOException {
		return title.replace('.', ' ').toLowerCase().trim().split("[\\,\\s!;?:\"]+");
	}
}

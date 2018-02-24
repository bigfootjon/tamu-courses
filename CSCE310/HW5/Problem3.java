import java.sql.*;
import java.util.*;
import java.io.*;
import java.text.SimpleDateFormat;

public class Problem3 {
	Connection conn = null;
	String className;
	Scanner scanner;
	ArrayList<String> patentList = null;

	public static void main(String[] args) {
		if (args.length != 2) {
			System.out.println("Please supply an username and password as args");
			return;
		}
		new Problem3(args[0], args[1]);
	}

	public Problem3(String username, String password) {
		try {
			Class.forName("com.mysql.jdbc.Driver").newInstance();
		} catch (Exception e) {
			e.printStackTrace();
			return;
		}
		try {
			conn = DriverManager.getConnection("jdbc:mysql://database2.cs.tamu.edu/jonjanzen-patentdb?user=" + username + "&password=" + password);
		} catch (SQLException e) {
			e.printStackTrace();
			return;
		}
		scanner = new Scanner(System.in);
		String fileName = "";
		while (patentList == null && !fileName.equals("quit")) {
			fileName = askUser("JSON file name (default: patent1-1000JSON.ser)");
			if (fileName.equals("")) {
				fileName = "patent1-1000JSON.ser";
			}
			try {
				FileInputStream fis = new FileInputStream(fileName);
				ObjectInputStream ois = new ObjectInputStream(fis);
				patentList = (ArrayList<String>) ois.readObject();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		System.out.println("Patent count: " + patentList.size());
		for (String patentString : patentList) {
			insertPatent(patentString);
		}
		try {
			conn.close();
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	private String askUser(String query) {
		System.out.print(query + ": ");
		return scanner.nextLine();
	}

	private Integer getOrCreatePerson(String name) {
		if (name == null ) {
			return null;
		}
		if (name.length() > 100) {
			name = name.substring(0,100);
		}
		name = name.replaceAll("'", "");
		String getQuery = "SELECT id FROM person WHERE name='" + name + "'";
		String create = "INSERT INTO person (name, location) VALUES ('" + name + "', NULL)";
		Statement statement = null;
		try {
			statement = conn.createStatement();
			ResultSet rs = statement.executeQuery(getQuery);
			if (rs.next()) {
				return rs.getInt("id");
			}
			statement.executeUpdate(create);
			rs = statement.executeQuery(getQuery);
			if (rs.next()) {
				return rs.getInt("id");
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			try {
				if (statement != null) {
					statement.close();
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
		return null;
	}

	private void insertPatent(String patentString) {
		String assigneeString = getColumn(patentString, "assignee");
		Integer assigneeId = getOrCreatePerson(assigneeString);

		String examinerString = getColumn(patentString, "examiner");
		Integer examinerId = getOrCreatePerson(examinerString);

		String legalFirmString = getColumn(patentString, "legalfirm");
		Integer legalFirmId = getOrCreatePerson(legalFirmString);

		String patentNumber = getColumn(patentString, "patNum");
		String issueDate = getSqlDate(getColumn(patentString, "iDate"));
		String title = getColumn(patentString, "title");
		String patentAbstract = getColumn(patentString, "abstract");
		String familyId = getColumn(patentString, "familyID");
		String appNum = getColumn(patentString, "applNum");
		String dateFiled = getSqlDate(getColumn(patentString, "dateFiled"));
		String docId = getColumn(patentString, "docID");
		String pubDate = getSqlDate(getColumn(patentString, "pubDate"));
		String usClass = getColumn(patentString, "USclass");
		String summary = getColumn(patentString, "summary");
		String description = getColumn(patentString, "description");

		String query = "INSERT INTO patent (number, dateIssued, title, abstract, assignee, familyId, appNum, dateFiled, docId, pubDate, usClass, examiner, legalFirm, summary, description) VALUES (" + patentNumber + ", " + issueDate + ", '" + title + "', '" + patentAbstract + "', " + assigneeId + ", " + familyId + ", '" + appNum + "', " + dateFiled + ", '" + docId + "', " + pubDate + ", '" + usClass + "', " + examinerId + ", " + legalFirmId + ", '" + summary + "', '" + description + "')";
		Statement statement = null;
		try {
			statement = conn.createStatement();
			statement.executeUpdate(query);
		} catch (SQLException e) {
			e.printStackTrace();
			System.err.println(query);
		} finally {
			try {
				if (statement != null) {
					statement.close();
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
	}

	private String getColumn(String patentString, String column) {
		String columnStr = "\""+column+"\":\"";
	        int startIndex = patentString.indexOf(columnStr);
	        if (startIndex != -1) {
	        	String columnData = patentString.substring(startIndex + columnStr.length());
	        	String endStr = "\",\"";
	        	int endIndex = columnData.indexOf(endStr);
			if (endIndex != -1) {
	        		String result = columnData.substring(0, endIndex);
				if (result.equals("")) {
					return null;
				}
				return result.replaceAll("'", "''");
			}
	        	String endAltStr = "\"}";
	        	int endAltIndex = columnData.indexOf(endAltStr);
			if (endAltIndex != -1) {
	        		String result = columnData.substring(0, endAltIndex);
				if (result.equals("")) {
					return null;
				}
				return result.replaceAll("'", "''");
			}
		}
		System.out.println("Column not found: " + column);
		return null;
	}

	private String getSubObject(String patentString, String name) {
		// TODO
	}

	SimpleDateFormat jsonFormat = new SimpleDateFormat("MMM dd, yyyy");
	SimpleDateFormat sqlFormat = new SimpleDateFormat("yyyy-MM-dd");

	private String getSqlDate(String date) {
		try {
			return "'" + sqlFormat.format(jsonFormat.parse(date)) + "'";
		} catch (Exception e) {
			return null;
		}
	}
}

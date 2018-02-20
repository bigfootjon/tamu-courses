import java.sql.*;
import java.util.*;
import java.io.*;

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
			conn = DriverManager.getConnection("jdbc:mysql://database2.cs.tamu.edu/jonjanzen-shipsdb?user=" + username + "&password=" + password);
		} catch (SQLException e) {
			e.printStackTrace();
			return;
		}
		scanner = new Scanner(System.in);
		String fileName = "";
		while (patentList == null && !fileName.equals("quit")) {
			fileName = askUser("JSON file name");
			try {
				FileInputStream fis = new FileInputStream(fileName);
				ObjectInputStream ois = new ObjectInputStream(fis);
				patentList = (ArrayList<String>) ois.readObject();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		System.out.println("Patent count: " + patentList.size());
		// READ DATA HERE
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

	private void newShips() {
		String shipName = className;
		String query = "INSERT INTO ships (name, class, launched) VALUES ()";
		Statement statement = null;
		try {
			statement = conn.createStatement();
			statement.executeUpdate(query);
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
	}
}

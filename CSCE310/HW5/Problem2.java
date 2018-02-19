import java.sql.*;
import java.util.Scanner;

public class Problem2 {
	Connection conn = null;
	String className;
	Scanner scanner;

	public static void main(String[] args) {
		if (args.length != 2) {
			System.out.println("Please supply an username and password as args");
			return;
		}
		new Problem2(args[0], args[1]);
	}

	public Problem2(String username, String password) {
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
		newClass();
		newShips();
		
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

	private void newClass() {
		className = askUser("Class name");
		String type = askUser("Class type");
		String country = askUser("Class country");
		String numGuns = askUser("Class gun count");
		String bore = askUser("Class bore");
		String disp = askUser("Class displacement");
		String query = "INSERT INTO classes (class, type, country, numGuns, bore, disp) VALUES ('" + className + "', '" + type + "', '" + country + "', " + numGuns + ", " + bore + ", " + disp + ");";
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

	private void newShips() {
		String shipName = className;
		System.out.println("Ship name ('exit' to finish): " + shipName);
		while (!shipName.equals("exit")) {
			String launched = askUser("Ship launch year");
			String query = "INSERT INTO ships (name, class, launched) VALUES ('" + shipName + "', '" + className + "', " + launched + ")";
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
			shipName = askUser("Ship name ('exit' to finish)");
		}
		}
	}
}

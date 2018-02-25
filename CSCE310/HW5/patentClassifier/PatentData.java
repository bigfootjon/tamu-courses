package patentClassifier;

import java.sql.*;

public class PatentData {
	Connection conn = null;
	ResultSet patents = null;
	int rsIndex = 0;
	
	public PatentData(String username, String password) throws Exception {
		Class.forName("com.mysql.jdbc.Driver").newInstance();
		conn = DriverManager.getConnection("jdbc:mysql://database2.cs.tamu.edu/jonjanzen-patentdb?user=" + username + "&password=" + password);
		String query = "SELECT * FROM patent";
		Statement statement = conn.createStatement();
		patents = statement.executeQuery(query);
		patents.next();
	}
	
	public String getPatentField(int index, String field) throws SQLException {
		if (rsIndex > index) {
			patents.beforeFirst();
			patents.next();
			rsIndex = 0;
		}
		do {
			if (index == rsIndex) {
				return patents.getString(field);
			}
			rsIndex++;
		} while (patents.next());
		return null;
	}
}

import java.sql.*;

public class Problem1 {
	public static void main(String[] args) {
		try {
			Class.forName("com.mysql.jdbc.Driver").newInstance();
		} catch (Exception e) {
			e.printStackTrace();
			return;
		}
		Connection conn;
		try {
			conn = DriverManager.getConnection("jdbc:mysql://database2.cs.tamu.edu/jonjanzen-shipsdb?user=jonjanzen&password=Jkl777919");
			Statement stmt = conn.createStatement();
			String qry = "SELECT * FROM classes";
			ResultSet rs = stmt.executeQuery(qry);
			while (rs.next()) {
				System.out.println(rs.getString("Name"));
			}
		} catch (SQLException e) {
			e.printStackTrace();
			return;
		}
	}
}

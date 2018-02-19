import java.sql.*;
import java.util.Scanner;

public class Problem1 {
	Connection conn = null;
	String className;
	Scanner scanner;

	public static void main(String[] args) {
		new Problem1();
	}

	public Problem1() {
		try {
			conn = DriverManager.getConnection("jdbc:derby:/Users/jonjanzen/manfDB");
		} catch (SQLException e) {
			e.printStackTrace();
			return;
		}
		scanner = new Scanner(System.in);
		
		String manf = askUser("Manufacturer");
		String select_product = "product.model, product.type";
		String select_pc = "pc.speed AS pc_speed, pc.ram AS pc_ram, pc.hd AS pc_hd, pc.price AS pc_price";
		String select_laptop = "laptop.speed AS laptop_speed, laptop.ram AS laptop_ram, laptop.hd AS laptop_hd, laptop.screen AS laptop_screen, laptop.price AS laptop_price";
		String select_printer = "printer.color AS printer_color, printer.type AS printer_type, printer.price AS printer_price";
		String select = select_product + ", " + select_pc + ", " + select_laptop + ", " + select_printer;
		String joins = "LEFT OUTER JOIN pc ON Product.model = pc.model LEFT OUTER JOIN laptop ON Product.model = laptop.model LEFT OUTER JOIN printer on product.model = printer.model";
		String query = "SELECT " + select + " FROM Product " + joins + " WHERE maker = '" + manf + "'";
		try {
			Statement statement = conn.createStatement();
			ResultSet rs = statement.executeQuery(query);
			while (rs.next()) {
				String type = rs.getString("type");
				String model = rs.getString("model");
				if (type.equals("pc")) {
					String speed = rs.getString("pc_speed");
					String ram = rs.getString("pc_ram");
					String hd = rs.getString("pc_hd");
					String price = rs.getString("pc_price");
					System.out.println("pc: model=" + model + ", speed=" + speed + ", ram=" + ram + ", hd=" + hd + ", price=" + price);
				} else if (type.equals("laptop")) {
					String speed = rs.getString("laptop_speed");
					String ram = rs.getString("laptop_ram");
					String hd = rs.getString("laptop_hd");
					String screen = rs.getString("laptop_screen");
					String price = rs.getString("laptop_price");
					System.out.println("laptop: model=" + model + ", speed=" + speed + ", ram=" + ram + ", hd=" + hd + ", screen=" + screen + ", price=" + price);
				} else if (type.equals("printer")) {
					String color = rs.getString("printer_color");
					String printer_type = rs.getString("printer_type");
					String price = rs.getString("printer_price");
					System.out.println("printer: model=" + model + ", color=" + color + ", type=" + printer_type + ", price=" + price);
				} else {
					System.out.println(type + ": ?");
				}
			}
		
			conn.close();
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	private String askUser(String query) {
		System.out.print(query + ": ");
		return scanner.nextLine();
	}
}

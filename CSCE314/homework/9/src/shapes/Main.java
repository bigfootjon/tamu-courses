package shapes;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        new Main(args);
    }

    private Main(String[] args) {
        Shape[] shapes = new Shape[args.length];
        for (int i = 0; i < args.length; i++) {
            String arg = args[i];
            Shape s = parseShape(arg);
            shapes[i] = s;
        }
        AreaCalculator ac = new AreaCalculator();
        double area = ac.calculate(shapes);
        System.out.printf("The total area for the %d objects is %1.2f units squared\n", shapes.length, area);
    }

    private Point parsePoint(Scanner s) {
        double x = s.nextDouble();
        double y = s.nextDouble();
        Point toReturn = new Point(x, y);
        System.out.println(toReturn);
        return toReturn;
    }

    private Circle parseCircle(Scanner s) {
        System.out.println("Circle:");
        Point center = parsePoint(s);
        double radius = s.nextDouble();
        System.out.println(radius);
        return new Circle(center, radius);
    }

    private Rectangle parseRectangle(Scanner s) {
        System.out.println("Rectangle:");
        Point tl = parsePoint(s);
        Point br = parsePoint(s);
        return new Rectangle(tl, br);
    }

    private Triangle parseTriangle(Scanner s) {
        System.out.println("Triangle:");
        Point a = parsePoint(s);
        Point b = parsePoint(s);
        Point c = parsePoint(s);
        return new Triangle(a, b, c);
    }

    private Shape parseShape(String input) {
        char shapeType = input.charAt(0);
        String rest = input.substring(2);
        Scanner s = new Scanner(rest);
        switch (shapeType) {
            case 't': return parseTriangle(s);
            case 'r': return parseRectangle(s);
            case 'c': return parseCircle(s);
            default: return null;
        }
    }
}

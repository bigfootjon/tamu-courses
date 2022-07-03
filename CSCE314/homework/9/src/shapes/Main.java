package shapes;

import java.util.Arrays;
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

        Circle c1 = new Circle(new Point(1,1),1);
        Circle d1 = new Circle(new Point(2,2),2);
        Circle e1 = new Circle(new Point(3,3),3);

        ShapeList<Shape> emptyShapes = new ShapeList<>();
        ShapeList<Circle> someCircles = new ShapeList<>(Arrays.asList(c1, d1, e1));

        System.out.println("emptyShapes = " + emptyShapes);
        System.out.println("reversed emptyShapes = " + emptyShapes.reverse());
        System.out.println("someCircles = " + someCircles);
        System.out.println("reversed someCircles = " + someCircles.reverse());

        double sumOfXs = 0.0;
        double sumOfYs = 0.0;
        for (Circle c: someCircles) {
            sumOfXs += c.position().x;
            sumOfYs += c.position().y;
        }
        System.out.println("Some of Xs = " + sumOfXs);
        System.out.println("Some of Ys = " + sumOfYs);
    }

    private Point parsePoint(Scanner s) {
        double x = s.nextDouble();
        double y = s.nextDouble();
        return new Point(x, y);
    }

    private Circle parseCircle(Scanner s) {
        Point center = parsePoint(s);
        double radius = s.nextDouble();
        return new Circle(center, radius);
    }

    private Rectangle parseRectangle(Scanner s) {
        Point tl = parsePoint(s);
        Point br = parsePoint(s);
        return new Rectangle(tl, br);
    }

    private Triangle parseTriangle(Scanner s) {
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

    public static Shape maxArea(Node<Shape> root) {
        Shape max = root.v;
        double max_area = max.area();
        for (Shape s : root) {
            double s_area = s.area();
            if (s_area > max_area) {
                max = s;
                max_area = s_area;
            }
        }
        return max;
    }

    public static Rectangle boundingRect(Node<Rectangle> root) {
        double tlx = root.v.tl.x;
        double tly = root.v.tl.y;
        double brx = root.v.br.x;
        double bry = root.v.br.y;

        for (Rectangle r : root) {
            if (r.tl.x < tlx) {
                tlx = r.tl.x;
            }
            if (r.tl.y < tly) {
                tly = r.tl.y;
            }
            if (r.br.x > brx) {
                brx = r.br.x;
            }
            if (r.br.y > bry) {
                bry = r.br.y;
            }
        }

        Point tl = new Point(tlx, tly);
        Point br = new Point(brx, bry);
        return new Rectangle(tl, br);
    }
}

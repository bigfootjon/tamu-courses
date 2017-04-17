package shapes;

public class Circle extends Shape {
    private final Point center;
    private final double radius;

    public Circle(Point center, double radius) {
        this.center = center;
        this.radius = radius;
    }

    @Override
    Point position() {
        return center;
    }

    @Override
    double area() {
        return Math.PI * Math.pow(radius, 2);
    }
}

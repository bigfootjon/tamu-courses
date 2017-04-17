package shapes;

public class Circle extends Shape {
    private final Point center;
    private final double radius;

    Circle(Point center, double radius) {
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

    @Override
    public boolean equals(Object o) {
        if (o instanceof Circle) {
            Circle c = (Circle)o;
            return center.equals(c.center) && radius == c.radius;
        } else {
            return false;
        }
    }
}

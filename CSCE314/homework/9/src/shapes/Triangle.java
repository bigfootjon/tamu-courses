package shapes;

public class Triangle extends Shape {
    private final Point a, b, c;

    public Triangle(Point a, Point b, Point c) {
        this.a = a;
        this.b = b;
        this.c = c;
    }

    @Override
    Point position() {
        // calculates centroid
        return Point.averageOf(a, b, c);
    }

    @Override
    double area() {
        double sa = Math.sqrt(Math.pow(b.x - a.x, 2) + Math.pow(b.y - a.y, 2));
        double sb = Math.sqrt(Math.pow(c.x - b.x, 2) + Math.pow(c.y - b.y, 2));
        double sc = Math.sqrt(Math.pow(a.x - c.x, 2) + Math.pow(a.y - c.y, 2));
        double s = (sa+sb+sc)/2;
        return Math.sqrt(s*(s-sa)*(s-sb)*(s-sc));
    }
}

package shapes;

public class Rectangle extends Shape {
    private final Point tl;
    private final Point br;

    Rectangle(Point tl, Point br) {
        this.tl = tl;
        this.br = br;
    }

    @Override
    Point position() {
        return Point.averageOf(tl, br);
    }

    @Override
    double area() {
        return Math.abs(tl.x - br.x) * Math.abs(tl.y - br.y);
    }

    @Override
    public boolean equals(Object o) {
        if (o instanceof Rectangle) {
            Rectangle r = (Rectangle)o;
            return tl.equals(r.tl) && br.equals(r.br);
        } else {
            return false;
        }
    }

    @Override
    public String toString() {
        return "Rectangle " + tl.toString() + "-" + br.toString();
    }
}

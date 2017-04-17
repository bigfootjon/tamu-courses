package shapes;

public class Rectangle extends Shape {
    private final Point tl;
    private final Point br;

    public Rectangle(Point tl, Point br) {
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
}

package shapes;

class Point {
    double x, y;

    Point(double x, double y) {
        this.x = x;
        this.y = y;
    }

    static Point averageOf(Point... points) {
        int count = points.length;
        int xs = 0;
        int ys = 0;
        for (Point p : points) {
            xs += p.x;
            ys += p.y;
        }
        return new Point(xs/count, ys/count);
    }

    @Override
    public String toString() {
        return "(" + x + ", " + y + ")";
    }

    @Override
    public boolean equals(Object o) {
        if (o instanceof Point) {
            Point p = (Point)o;
            return x == p.x && y == p.y;
        } else {
            return false;
        }
    }
}

package shapes;

public abstract class Shape implements Comparable<Shape> {
    abstract Point position();
    abstract double area();

    @Override
    public abstract boolean equals(Object obj);

    @Override
    public int compareTo(Shape o) {
        double ta = area();
        double oa = o.area();
        double diff = ta - oa;
        if (diff == 0) {
            // This avoids dividing by 0 in the "else" branch
            return 0;
        } else {
            // reduce magnitude to 1 while maintaining sign.
            return (int) (diff / Math.abs(diff));
        }
    }
}

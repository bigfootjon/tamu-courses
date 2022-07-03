package shapes;

public class AreaCalculator {
    public double calculate(Shape[] shapes) {
        double soFar = 0;
        for (Shape s : shapes) {
            soFar += s.area();
        }
        return soFar;
    }
}

package part2;

public class Counter {
    private int counter = 0;

    public synchronized void increment() {
        counter++;
    }

    public synchronized int get() {
        return counter;
    }
}

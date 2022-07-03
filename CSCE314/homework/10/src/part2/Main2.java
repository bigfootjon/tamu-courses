package part2;

public class Main2 {
    public static void main(String[] args) {
        Counter shared = new Counter();
        Thread message7 = new Thread(new MessageRunnable(shared, 7));
        Thread message15 = new Thread(new MessageRunnable(shared, 15));
        Thread increment = new Thread(new IncrementRunnable(shared, new Thread[] {message7, message15}));
        message7.start();
        message15.start();
        increment.start();
    }
}

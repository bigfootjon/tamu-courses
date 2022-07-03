package part2;

public class IncrementRunnable implements Runnable {

    private Counter shared;
    private Thread[] threads;

    IncrementRunnable(Counter shared, Thread[] threads) {
        this.shared = shared;
        this.threads = threads;
    }

    @Override
    public void run() {
        while (true) {
            shared.increment();
            for (Thread t : threads) {
                t.interrupt();
            }
            System.out.print(shared.get() + " ");
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

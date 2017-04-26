package part2;

public class MessageRunnable implements Runnable {
    private Counter shared;
    private int interval;

    MessageRunnable(Counter shared, int interval) {
        this.shared = shared;
        this.interval = interval;
    }

    @Override
    public void run() {
        while (true) {
            try {
                Thread.sleep(Long.MAX_VALUE);
            } catch (InterruptedException ignored) {
                if (shared.get() % interval == 0) {
                    System.out.println();
                    System.out.println(shared.get() + " second message");
                }
            }
        }
    }
}

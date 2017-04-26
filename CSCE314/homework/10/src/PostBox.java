import java.util.*;
import java.util.concurrent.locks.ReentrantLock;

class PostBox implements Runnable {
    private static final int MAX_SIZE = 10;

    class Message {
        String sender;
        String recipient;
        String msg;

        Message(String sender, String recipient, String msg) {
            this.sender = sender;
            this.recipient = recipient;
            this.msg = msg;
        }
    }

    private final LinkedList<Message> messageQueue;
    private final ReentrantLock queueModLock;
    private LinkedList<Message> myMessages;
    private String myId;
    private boolean stop = false;

    PostBox(String myId) {
        this.myId = myId;
        this.messageQueue = new LinkedList<>();
        this.queueModLock = new ReentrantLock();
        this.myMessages = new LinkedList<>();
        new Thread(this).start();
    }

    PostBox(String myId, PostBox p) {
        this.myId = myId;
        this.messageQueue = p.messageQueue;
        this.queueModLock = p.queueModLock;
        this.myMessages = new LinkedList<>();
        new Thread(this).start();
    }

    private String getId() { return myId; }

    void stop() {
        this.stop = true;
    }

    void send(String recipient, String msg) {
        Message m = new Message(getId(), recipient, msg);
        queueModLock.lock();
        messageQueue.add(m);
        queueModLock.unlock();
    }

    List<String> retrieve() {
        queueModLock.lock();
        List<String> result = new ArrayList<>();
        for (Message m : myMessages) {
            String stringyM = m.sender + ": " + m.msg;
            result.add(stringyM);
        }
        myMessages.clear();
        queueModLock.unlock();
        return result;
    }

    public void run() {
        while (!stop) {
            queueModLock.lock();
            for (Iterator<Message> iterator = messageQueue.iterator(); iterator.hasNext(); ) {
                Message m = iterator.next();
                if (m.sender.equals(getId())) {
                    myMessages.add(m);
                } else {
                    iterator.remove();
                }
            }

            while (messageQueue.size() > MAX_SIZE) {
                messageQueue.remove(0);
            }
            queueModLock.unlock();
            try {
                Thread.sleep(1000);
            } catch (InterruptedException ignored) {}
        }
    }
}

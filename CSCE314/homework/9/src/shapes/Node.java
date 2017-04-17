package shapes;

import java.util.Iterator;

public final class Node<T extends Shape> implements Iterable<T> {
    final T v;
    Node<T> next;

    Node(T val, Node<T> next) {
        v = val;
        this.next = next;
    }

    @Override
    public Iterator<T> iterator() {
        return new NodeIterator<>(this);
    }
}

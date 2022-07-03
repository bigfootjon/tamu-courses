package shapes;

import java.util.Iterator;

public class NodeIterator<T extends Shape> implements Iterator<T> {
    private Node<T> cur;
    private Node<T> last;

    NodeIterator(Node<T> shape) {
        this.cur = shape;
        this.last = null;
    }

    @Override
    public boolean hasNext() {
        return cur.next != null;
    }

    @Override
    public T next() {
        if (last == null) {
            last = cur;
            return cur.v;
        } else {
            last = cur;
            if (cur.next == null){
                return null;
            } else {
                cur = cur.next;
                return cur.v;
            }
        }
    }

    @Override
    public void remove() {
        last.next = cur.next;
    }
}

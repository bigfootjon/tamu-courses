package shapes;

import java.util.ArrayList;
import java.util.Iterator;

public class ShapeList<T extends Shape> implements Iterable<T> {
    private Node<T> root = null;

    ShapeList(Iterable<T> iterable) {
        Node<T> cur = null;
        for (T a : iterable) {
            Node<T> next = new Node<>(a, null);
            if (cur == null) {
                root = next;
                cur = next;
            } else {
                cur.next = next;
                cur = next;
            }
        }
    }

    ShapeList() {}

    @Override
    public Iterator<T> iterator() {
        return root.iterator();
    }

    ShapeList<T> reverse() {
        ArrayList<T> tempList = new ArrayList<>();
        if (root != null) {
            for (T a : this) {
                tempList.add(a);
            }
        }
        return new ShapeList<>(tempList);
    }

    public String toString() {
        StringBuilder result = new StringBuilder("[");
        if (root != null) {
            for (Iterator<T> iterator = root.iterator(); iterator.hasNext(); ) {
                T a = iterator.next();
                result.append("{").append(a).append("}");
                if (iterator.hasNext()) {
                    result.append(", ");
                }
            }
        }
        result.append("]");
        return result.toString();
    }
}

abstract class Animal {
    private final String name;
    private int order;

    Animal(String name) {
        this.name = name;
        this.order = 0;
    }

    final String getName() {
        return name;
    }

    final void decrementOrder() {
        this.order--;
    }

    final int getOrder() {
        return order;
    }

    final void setOrder(int order) {
        this.order = order;
    }

    abstract String cry();

    @Override
    public String toString() {
        return getName() + ": " + getOrder() + " \"" + cry() + "\"";
    }
}

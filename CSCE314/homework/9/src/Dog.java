public class Dog extends Animal {
    public Dog(String name) {
        super(name);
    }

    @Override
    String cry() {
        return "bark";
    }
}

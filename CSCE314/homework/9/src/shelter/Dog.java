package shelter;

class Dog extends Animal {
    Dog(String name) {
        super(name);
    }

    @Override
    String cry() {
        return "bark";
    }
}

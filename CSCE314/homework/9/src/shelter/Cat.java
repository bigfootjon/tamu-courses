package shelter;

class Cat extends Animal {
    Cat(String name) {
        super(name);
    }

    @Override
    String cry() {
        return "meow";
    }
}

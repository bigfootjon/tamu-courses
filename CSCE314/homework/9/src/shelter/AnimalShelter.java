package shelter;

import java.util.ArrayList;
import java.util.List;

class AnimalShelter {
    private List<Animal> animals = new ArrayList<>();

    void addAnimal(Animal a) {
        a.setOrder(animals.size());
        animals.add(a);
    }

    private enum AdoptType {
        ANY,
        DOG,
        CAT;

        boolean matches(Animal a) {
            switch (this) {
                case DOG: return a instanceof Dog;
                case CAT: return a instanceof Cat;
                default: return true;
            }
        }
    }

    private Animal adopt(AdoptType type) {
        int index = -1;
        int order = 0;

        for (int i = 0; i < animals.size(); i++) {
            Animal a = animals.get(i);
            if (type.matches(a)) {
                if (a.getOrder() > order) {
                    index = i;
                    order = a.getOrder();
                }
            }
        }

        if (index < 0) {
            Animal toReturn = animals.remove(index);

            for (Animal a : animals) {
                if (a.getOrder() > order) {
                    a.decrementOrder();
                }
            }
            return toReturn;
        } else {
            return null;
        }
    }

    Animal adopt() {
        return adopt(AdoptType.ANY);
    }

    Animal adoptDog() {
        return adopt(AdoptType.DOG);
    }

    Animal adoptCat() {
        return adopt(AdoptType.CAT);
    }

    private void remaining(AdoptType type) {
        for (Animal a : animals) {
            if (type.matches(a)) {
                System.out.println(a);
            }
        }
    }

    void remainingAnimals() {
        remaining(AdoptType.ANY);
    }

    void remainingDogs() {
        remaining(AdoptType.DOG);
    }

    void remainingCats() {
        remaining(AdoptType.CAT);
    }
}

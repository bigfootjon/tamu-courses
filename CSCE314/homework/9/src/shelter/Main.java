package shelter;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        new Main(args);
    }

    private Main(String[] args) {
        AnimalShelter shelter = new AnimalShelter();

        for (String arg : args) {
            Animal a = parse(arg);
            if (a != null) {
                shelter.addAnimal(a);
            }
        }

        Scanner scanner = new Scanner(System.in);

        System.out.println("1. Add a new animal");
        System.out.println("2. Adopt an animal");
        System.out.println("3. Adopt a cat");
        System.out.println("4. Adopt a dog");
        System.out.println("5. Show animals in shelter");
        System.out.println("6. Show cats in shelter");
        System.out.println("7. Show dogs in shelter");
        System.out.println("0. Exit");

        while (true) {
            System.out.print("Enter a number: ");
            int input = scanner.nextInt();
            scanner.nextLine();
            switch (input) {
                case 1: // add
                    System.out.print("Input with the format \"t name\" where t is one of {d,c}: ");
                    String line = scanner.nextLine();
                    Animal a = parse(line);
                    if (a != null) {
                        shelter.addAnimal(a);
                    }
                    break;
                case 2: System.out.println(shelter.adopt()); break;
                case 3: System.out.println(shelter.adoptCat()); break;
                case 4: System.out.println(shelter.adoptDog()); break;
                case 5: shelter.remainingAnimals(); break;
                case 6: shelter.remainingCats(); break;
                case 7: shelter.remainingDogs(); break;
                default: return;
            }
        }
    }

    private Animal parse(String input) {
        char type = input.charAt(0);
        String name = input.substring(2);
        switch (type) {
            case 'c': return new Cat(name);
            case 'd': return new Dog(name);
            default:
                System.out.println("Parsing error occurred on: " + input);
                return null;
        }
    }
}

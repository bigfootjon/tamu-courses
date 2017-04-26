package part4;

import java.lang.reflect.Method;
import java.lang.reflect.Modifier;

public class Main4 {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please pass a classname to test!");
            System.exit(1);
        }
        String className = args[0];
        Class toTest;
        try {
            toTest = Class.forName(className);
            for (Method m : toTest.getMethods()) {
                int mods = m.getModifiers();
                if (Modifier.isStatic(mods) && Modifier.isPublic(mods) && ) {

                }
            }
        } catch (ClassNotFoundException ignored) {
            System.out.println("Class not found!");
            System.exit(2);
        }
    }
}

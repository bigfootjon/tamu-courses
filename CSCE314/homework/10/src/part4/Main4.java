package part4;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;

public class Main4 {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please pass a classname to test!");
            System.exit(1);
        }
        String className = args[0];
	    try {
            Class toTest = Class.forName(className);
            Object toUse = toTest.newInstance();
            for (Method m : toTest.getMethods()) {
                int mods = m.getModifiers();
                if (Modifier.isStatic(mods) && Modifier.isPublic(mods)) { // public static methods
	                if (m.getName().startsWith("test") && m.getReturnType() == boolean.class && m.getParameterCount() == 0) { // requirements to be a test
	                    boolean testSucceeded = (boolean) m.invoke(toUse);
	                    if (testSucceeded) {
		                    System.out.println("OK: " + m.getName() + " succeeded");
	                    } else {
		                    System.out.println("FAILED: " + m.getName() + " failed");
	                    }
                    }
                }
            }
        } catch (ClassNotFoundException ignored) {
            System.out.println("Class not found!");
            System.exit(2);
        } catch (IllegalAccessException | InstantiationException | InvocationTargetException ignored) {}
    }
}

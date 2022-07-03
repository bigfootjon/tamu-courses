package part3;

import java.lang.reflect.Method;
import java.lang.reflect.Modifier;

public class Main3 {
    public static void main(String[] args) {
        displayMethodInfo(new Example());
    }

    static class Example {
        void foo(int a, boolean b) {}
        int bar(int a, boolean b, long c) {return 0;}
        static double doo() {return 0;}
    }

    private static void displayMethodInfo(Object o) {
        Class a = o.getClass();
        Method[] methods = a.getDeclaredMethods();
        for (Method m : methods) {
            System.out.print(m.getName());
            System.out.print(" (");
            if (!Modifier.isStatic(m.getModifiers())) {
                System.out.print("THIS, ");
            }
            Class[] parameterTypes = m.getParameterTypes();
            for (int i = 0; i < parameterTypes.length; i++) {
                if (i != 0) {
                    System.out.print(", ");
                }
                System.out.print(parameterTypes[i]);
            }
            System.out.print(") -> ");
            System.out.println(m.getReturnType());
        }
    }
}

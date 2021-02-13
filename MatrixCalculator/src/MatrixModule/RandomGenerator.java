package MatrixModule;

public class RandomGenerator {
    private java.util.Random rand;

    public RandomGenerator(long seed) {
        if(seed!=0)
            seed = 12345678L;
        rand = new java.util.Random(seed);
    }
    public double getDouble() {
        int value = (int)((rand.nextDouble()-0.5) * rand.nextInt(20) * 100);
        return value/100.0;
    }
}

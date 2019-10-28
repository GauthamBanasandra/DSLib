package UFDS;

public class UfdsClient {
    public static void main(String[] args) {
        Ufds ufds = new Ufds(10);
        ufds.unionSet(1, 8);
        ufds.unionSet(8, 9);
        ufds.unionSet(8, 3);

        System.out.printf("is same set (1, 9): %b\n", ufds.isSameSet(1, 9));
        System.out.printf("is same set (1, 4): %b\n", ufds.isSameSet(1, 4));
    }
}

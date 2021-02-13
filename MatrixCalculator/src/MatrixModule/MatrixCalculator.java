package MatrixModule;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class MatrixCalculator {
    private static HashMap<String, ComplexMatrix> matrixMap = new HashMap<>();
    private static java.util.Scanner scanner = new java.util.Scanner(System.in);

    public static void main(String[] args) {
        System.out.println("----MATRIX CALCULATOR----");

        String choice;
        while (true){
            System.out.println("1. Create matrix");
            System.out.println("2. Delete matrix");
            System.out.println("3. Show matricies");
            System.out.println("4. Add");
            System.out.println("5. Subtract");
            System.out.println("6. Multiply");
            System.out.println("7. Find Determinant");
            System.out.println("8. Find Submatrix");
            System.out.println("9. Exit");

            choice = scanner.nextLine();

            switch (choice){
                case "1":
                    CreateMatrix();
                    break;
                case "2":
                    DeleteMatrix();
                    break;
                case "3":
                    ShowMatricies();
                    break;
                case "4":
                    Add();
                    break;
                case "5":
                    Subtract();
                    break;
                case "6":
                    Multiply();
                    break;
                case "7":
                    FindDeterminant();
                    break;
                case "8":
                    FindSubmatrix();
                    break;
                case "9":
                    return;
                default:
                    System.out.println("Invalid choice");
            }
            System.out.println();
        }

    }

    public static void CreateMatrix(){
        System.out.println("Matrix name");
        String name = scanner.nextLine();
        System.out.println("Matrix Rows");
        int rows = scanner.nextInt();
        System.out.println("Matrix Columns");
        int cols = scanner.nextInt();

        double real, imaginary;

        ArrayList<ComplexNumber> complexNumbers = new ArrayList<>();
        for (int i = 0; i < rows; i++) {
            for(int j=0; j < cols; j++){
                System.out.println("Cell " + (i+1) + (j+1));
                System.out.println("Real: ");
                real = scanner.nextDouble();
                System.out.println("Imaginary: ");
                imaginary = scanner.nextDouble();
                complexNumbers.add(new ComplexNumber(real,imaginary));
            }
        }

        ComplexMatrix newMatrix = new ComplexMatrix(rows, cols, complexNumbers);
        matrixMap.put(name, newMatrix);
        System.out.println("Matrix created");
        scanner.nextLine();
    }
    public static void DeleteMatrix(){
        System.out.println("Matrix name");
        String name = scanner.nextLine();

        matrixMap.remove(name);
        System.out.println("Matrix deleted");
    }
    public static void ShowMatricies(){
        for (Map.Entry<String, ComplexMatrix> mapEntry : matrixMap.entrySet()) {
            System.out.println(mapEntry.getKey());
            System.out.println(mapEntry.getValue().toString());
            System.out.println("---");
        }
    }
    public static void Add(){
        System.out.println("Matrix 1: ");
        String name1 = scanner.nextLine();
        System.out.println("Matrix 2: ");
        String name2 = scanner.nextLine();

        ComplexMatrix matrix1 = matrixMap.get(name1);
        if(matrix1 == null){
            System.out.println("Matrix doesn't exist");
            return;
        }
        ComplexMatrix matrix2 = matrixMap.get(name2);
        if(matrix2 == null){
            System.out.println("Matrix doesn't exist");
            return;
        }


        ComplexMatrix result = matrix1.add(matrix2);
        if(result == null){
            System.out.println("Invalid result");
            return;
        }
        System.out.println("Result: ");
        System.out.println(result.toString());

        System.out.println("Save matrix? (y/n)");
        String save = scanner.nextLine();
        if(save.equals("y")) {
            System.out.println("Matrix name");
            String name = scanner.nextLine();
            matrixMap.put(name, result);
        }
    }
    public static void Subtract(){
        System.out.println("Matrix 1: ");
        String name1 = scanner.nextLine();
        System.out.println("Matrix 2: ");
        String name2 = scanner.nextLine();

        ComplexMatrix matrix1 = matrixMap.get(name1);
        if(matrix1 == null){
            System.out.println("Matrix doesn't exist");
            return;
        }
        ComplexMatrix matrix2 = matrixMap.get(name2);
        if(matrix2 == null){
            System.out.println("Matrix doesn't exist");
            return;
        }


        ComplexMatrix result = matrix1.subtract(matrix2);
        if(result == null){
            System.out.println("Invalid result");
            return;
        }
        System.out.println("Result: ");
        System.out.println(result.toString());

        System.out.println("Save matrix? (y/n)");
        String save = scanner.nextLine();
        if(save.equals("y")) {
            System.out.println("Matrix name");
            String name = scanner.nextLine();
            matrixMap.put(name, result);
        }
    }
    public static void Multiply(){
        System.out.println("Matrix 1: ");
        String name1 = scanner.nextLine();
        System.out.println("Matrix 2: ");
        String name2 = scanner.nextLine();

        ComplexMatrix matrix1 = matrixMap.get(name1);
        if(matrix1 == null){
            System.out.println("Matrix doesn't exist");
            return;
        }
        ComplexMatrix matrix2 = matrixMap.get(name2);
        if(matrix2 == null){
            System.out.println("Matrix doesn't exist");
            return;
        }


        ComplexMatrix result = matrix1.multiply(matrix2);
        if(result == null){
            System.out.println("Invalid result");
            return;
        }
        System.out.println("Result: ");
        System.out.println(result.toString());

        System.out.println("Save matrix? (y/n)");
        String save = scanner.nextLine();
        if(save.equals("y")) {
            System.out.println("Matrix name");
            String name = scanner.nextLine();
            matrixMap.put(name, result);
        }
    }
    public static void FindDeterminant(){
        System.out.println("Matrix 1: ");
        String name1 = scanner.nextLine();

        ComplexMatrix matrix1 = matrixMap.get(name1);
        if(matrix1 == null){
            System.out.println("Matrix doesn't exist");
            return;
        }

        ComplexNumber result = matrix1.determinant();
        if(result == null){
            System.out.println("Invalid result");
            return;
        }
        System.out.println("Determinant: ");
        System.out.println(result.toString());
    }
    public static void FindSubmatrix(){
        System.out.println("Matrix 1: ");
        String name1 = scanner.nextLine();

        ComplexMatrix matrix1 = matrixMap.get(name1);
        if(matrix1 == null){
            System.out.println("Matrix doesn't exist");
            return;
        }
        System.out.println(matrix1.toString());

        System.out.println("Row to delete");
        int row = scanner.nextInt();
        System.out.println("Column to delete");
        int col = scanner.nextInt();
        scanner.nextLine();

        ComplexMatrix result = matrix1.subMatrix(row, col);
        if(result == null){
            System.out.println("Invalid result");
            return;
        }
        System.out.println("Submatrix: ");
        System.out.println(result.toString());

        System.out.println("Save matrix? (y/n)");
        String save = scanner.nextLine();
        if(save.equals("y")) {
            System.out.println("Matrix name");
            String name = scanner.nextLine();
            matrixMap.put(name, result);
        }
    }
}

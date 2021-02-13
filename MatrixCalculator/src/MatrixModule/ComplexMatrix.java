package MatrixModule;
import java.util.List;

public class ComplexMatrix {
    public ComplexNumber[][] Matrix;
    private int rows;
    private int cols;

    public ComplexMatrix(ComplexMatrix original){
        this.Matrix = new ComplexNumber[original.rows][original.cols];
        this.rows = original.rows;
        this.cols = original.cols;

        for(int i=0; i<this.rows; i++){
            for (int j=0; j<this.cols; j++){
                this.Matrix[i][j] = original.Matrix[i][j];
            }
        }
    }
    public ComplexMatrix(int rows, int cols){
        this.Matrix = new ComplexNumber[rows][cols];
        this.rows = rows;
        this.cols = cols;
    }
    public ComplexMatrix(int rows, int cols, RandomGenerator rG){
        this.Matrix = new ComplexNumber[rows][cols];
        this.rows = rows;
        this.cols = cols;

        for(int i=0; i<rows; i++){
            for (int j=0; j<cols; j++){
                Matrix[i][j] = new ComplexNumber(rG.getDouble(), rG.getDouble());
            }
        }
    }
    public ComplexMatrix(int rows, int cols, List<ComplexNumber> complexNumbers){
        this.Matrix = new ComplexNumber[rows][cols];
        this.rows = rows;
        this.cols = cols;

        for(int i=0; i<rows; i++){
            for (int j=0; j<cols; j++){
                ComplexNumber tempNum = complexNumbers.remove(0);
                Matrix[i][j] = new ComplexNumber(tempNum.getReal(), tempNum.getImaginary());
            }
        }
    }

    @Override
    public String toString() {

        for (int i=0; i<this.rows; i++){
            System.out.print('[');
            for (int j = 0; j<this.cols; j++){
                System.out.print(this.Matrix[i][j].toString());
                if(j!=this.cols-1)
                    System.out.print(", ");
            }
            if (i==this.rows-1)
                continue;
            System.out.println(']');
        }
        return "]";
    }

    public ComplexMatrix add(ComplexMatrix matrix){
        if(this.rows==matrix.rows && this.cols==matrix.cols){
            ComplexMatrix newMatrix = new ComplexMatrix(this.rows, this.cols);
            for (int i=0; i<this.rows; i++){
                for (int j = 0; j<this.cols; j++){
                    newMatrix.Matrix[i][j] = this.Matrix[i][j].add(matrix.Matrix[i][j]);
                }
            }
            return newMatrix;
        }
        else
            return null;
    }
    public ComplexMatrix subtract(ComplexMatrix matrix){
        if(this.rows==matrix.rows && this.cols==matrix.cols){
            ComplexMatrix newMatrix = new ComplexMatrix(this.rows, this.cols);
            for (int i=0; i<this.rows; i++){
                for (int j = 0; j<this.cols; j++){
                    newMatrix.Matrix[i][j] = this.Matrix[i][j].subtract(matrix.Matrix[i][j]);
                }
            }
            return newMatrix;
        }
        else
            return null;
    }
    public ComplexMatrix multiply(ComplexMatrix matrix){
        if(this.cols==matrix.rows){
            ComplexMatrix newMatrix = new ComplexMatrix(this.rows, matrix.cols);
            for (int i=0; i<this.rows; i++){
                for (int j=0; j<matrix.cols; j++){
                    newMatrix.Matrix[i][j] = new ComplexNumber(0, 0);
                }
            }

            for (int i=0; i<this.rows; i++){
                for (int j = 0; j<matrix.cols; j++){
                    for (int z=0; z<this.cols; z++){
                        newMatrix.Matrix[i][j] = newMatrix.Matrix[i][j].add(this.Matrix[i][z].multiply(matrix.Matrix[z][j]));
                    }
                }
            }
            return newMatrix;
        }
        else
            return null;
    }
    
    public void assign(ComplexMatrix matrix){
        ComplexMatrix newMatrix = new ComplexMatrix(matrix);

        this.Matrix = newMatrix.Matrix;
        this.rows = newMatrix.rows;
        this.cols = newMatrix.cols;
    }

    public ComplexMatrix subMatrix(int delRow, int delCol){
        if(delRow<=this.rows-1 && delCol<=this.cols-1){
            ComplexMatrix newMatrix = new ComplexMatrix(this.rows-1, this.cols-1);
            int k=0, z=0;
            for (int i=0; i<this.rows; i++){
                if(i==this.rows-1 && delRow==this.rows-1)
                    break;
                else if(i==delRow)
                    i++;

                for (int j=0; j<this.cols; j++) {
                    if(j==this.cols-1 && delCol==this.cols-1)
                        break;
                    else if(j==delCol)
                        j++;
                    newMatrix.Matrix[k][z] = this.Matrix[i][j];
                    z++;
                }
                z=0;
                k++;
            }
            return newMatrix;
        }
        else
            return null;
    }
    public ComplexNumber determinant(){
        ComplexMatrix tempMatrix;
        ComplexNumber result = new ComplexNumber(0, 0);
        if((this.rows != this.cols) || (this.rows==0))
            return null;
        else {
            if (this.rows == 1)
                return this.Matrix[0][0];
            else if (this.rows == 2) {
                return (this.Matrix[0][0].multiply(this.Matrix[1][1])
                        .subtract(this.Matrix[0][1].multiply(this.Matrix[1][0])));
            }
            else {
                for (int colIteration=0; colIteration<this.cols; colIteration++){
                    tempMatrix = this.subMatrix(0, colIteration);
                    if (colIteration%2==1)
                        result = result.subtract(this.Matrix[0][colIteration].multiply(tempMatrix.determinant()));
                    else
                        result = result.add(this.Matrix[0][colIteration].multiply(tempMatrix.determinant()));
                }
                return result;
            }
        }
    }
}

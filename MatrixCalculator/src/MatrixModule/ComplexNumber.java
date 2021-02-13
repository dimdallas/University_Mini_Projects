package MatrixModule;

public class ComplexNumber {
    private double real;
    private double imaginary;

    public ComplexNumber(double conReal, double conImag){
        real = conReal;
        imaginary = conImag;
    }

    public ComplexNumber add(ComplexNumber num){
        ComplexNumber result = new ComplexNumber((this.real + num.real), (this.imaginary + num.imaginary));
        return result;
    }

    public ComplexNumber subtract(ComplexNumber num){
        ComplexNumber result = new ComplexNumber((this.real - num.real), (this.imaginary - num.imaginary));
        return result;
    }

    public ComplexNumber multiply(ComplexNumber num){
        ComplexNumber result = new ComplexNumber(((this.real*num.real) - (this.imaginary*num.imaginary)),
                ((this.real*num.imaginary) + (this.imaginary*num.real)));
        return result;
    }

    public String toString(){
        if(imaginary<0)
            return String.format("%.2f",real) + " - " + String.format("%.2f",Math.abs(imaginary))+'j';
        else
            return String.format("%.2f",real) + " + " + String.format("%.2f",Math.abs(imaginary))+'j';
    }

    public double getReal() {
        return real;
    }

    public double getImaginary() {
        return imaginary;
    }
}

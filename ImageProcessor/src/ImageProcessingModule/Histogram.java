package ImageProcessingModule;

import java.io.*;

public class Histogram {
    private int[][] imageIntensities;
    private int width;
    private int height;
    private int[] histogram;
    private int[] floorRounding = new int[236];

    public Histogram(YUVImage img) {
        width = img.getWidth();
        height = img.getHeight();
        imageIntensities = new int[img.getHeight()][img.getWidth()];

        histogram = new int[236];
        for (int i=0; i<236; i++)
            histogram[i] = 0;


        for (int i=0; i<img.getHeight(); i++){
            for (int j=0; j<img.getWidth(); j++){
                imageIntensities[i][j] = (img.getImage())[i][j].getY();
                int number = (img.getImage())[i][j].getY();
                histogram[number] = histogram[number] + 1;
            }
        }


    }

    @Override
    public String toString() {
        String histogramStr = "";
        String temp;

        for (int i=0; i<236; i++){
            temp = i + " ";
            for (int j = 0; j< histogram[i]; j++){
                temp = temp + "*";
            }
            histogramStr = temp + "\n";
        }
        return histogramStr;
    }

    public void toFile(File file){
        try {
            file = new File(String.valueOf(file));
            FileWriter writer = new FileWriter(file);

            writer.write(this.toString());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void equalize(){
        double[] probability = new double[236];
        double[] cumulativeP = new double[236];

        for (int i=0; i<236; i++){
            probability[i] = (double) histogram[i]/(height * width);
        }
        for (int i=0; i<236; i++){
            if (i==0)
                cumulativeP[i] = probability[i];
            else {
                cumulativeP[i] = probability[i] + cumulativeP[i-1];
            }
        }


        for (int i=0; i<236; i++)
            floorRounding[i] = (int) Math.floor(cumulativeP[i] * 235);

        for (int i=0; i<height; i++){
            for (int j=0; j<width; j++){
                int temp=imageIntensities[i][j];
                imageIntensities[i][j] = floorRounding[temp];
            }
        }

        for (int i=0; i<236; i++)
            histogram[i] = 0;

        for (int i=0; i<height; i++){
            for (int j=0; j<width; j++){
                histogram[imageIntensities[i][j]] = histogram[imageIntensities[i][j]] + 1;
            }
        }
    }

    public short getEqualizedLuminocity(int luminocity){
        return (short)floorRounding[luminocity];
    }
}

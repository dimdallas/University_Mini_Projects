package ImageProcessingModule;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class YUVImage {
    private int width;
    private int height;
    private YUVPixel[][] image;
    private File yuvFile;

    public YUVImage(int width, int height){
        this.width = width;
        this.height = height;

        image = new YUVPixel[this.height][this.width];

        for (int i=0; i<height; i++){
            for (int j=0; j<width; j++){
                image[i][j] = new YUVPixel((short)16, (short)128, (short)128);
            }
        }
    }

    public YUVImage(YUVImage copyImg){
        this.width = copyImg.getWidth();
        this.height = copyImg.getHeight();

        this.image = new YUVPixel[height][width];

        for (int i=0; i<height; i++){
            for (int j=0; j<width; j++){
                image[i][j] = new YUVPixel(copyImg.image[i][j]);
            }
        }
    }

    public YUVImage(RGBImage RGBImg){
        this.width = RGBImg.getWidth();
        this.height = RGBImg.getHeight();

        this.image = new YUVPixel[height][width];

        for (int i=0; i<height; i++){
            for (int j=0; j<width; j++){
                image[i][j] = new YUVPixel((RGBImg.getImage())[i][j]);
            }
        }
    }

    public YUVImage(File file) throws UnsupportedFileFormatException, FileNotFoundException{
        yuvFile = file;

            Scanner sc = new Scanner((new File(String.valueOf(file))));

            String magicCode = sc.next();
            if(!magicCode.equals("YUV3")){
                throw new UnsupportedFileFormatException("Wrong magic number");
            }

            int imgWidth=sc.nextInt();
            int imgHeight=sc.nextInt();

            if (imgHeight<=0 || imgWidth<=0) {
                throw new UnsupportedFileFormatException("Invalid height/width/colorDepth");
            }

            this.setHeight(imgHeight);
            this.setWidth(imgWidth);
            this.setImage();

            for (int i=0; i<height; i++){
                for (int j=0; j<width; j++){
                    image[i][j] = new YUVPixel((short)16, (short)128, (short)128);
                }
            }

            int i=0, j=0;
            short y, u, v;

            while (sc.hasNextInt()){
                y=(short)sc.nextInt();
                u=(short)sc.nextInt();
                v= (short)sc.nextInt();
                if (y > 255) {
                    y= (short) 235;
                } else if (u > 255) {
                    u= (short) 255;
                } else if (v > 255) {
                    v= (short) 255;
                }
                if(j==imgWidth){
                    i++;
                    j=0;
                }
                this.image[i][j]= new YUVPixel(y, u, v);
                j++;
            }

    }

    @Override
    public String toString() {
        String yuvStr = "";

        try {
            Scanner sc = new Scanner(new File(String.valueOf(yuvFile)));
            while (sc.hasNext()){
                yuvStr = yuvStr.concat(sc.next() +"\n");
            }
        } catch (FileNotFoundException e) {
            System.out.println("YUV Not Found");
        }
        return yuvStr;
    }

    public void toFile(File file) {
        try {
            file = new File(String.valueOf(file));
            yuvFile=file;
            if (!file.createNewFile()) {
                FileWriter writer = new FileWriter(file);
                writer.write("");
                writer.close();
                System.out.println("File overwritten");
            } else {
                System.out.println("File created");
            }
            FileWriter writer = new FileWriter(file);
            String yuvStr="YUV3\n" +
                    this.getWidth() + " " + this.getHeight() + "\n";

            writer.write(yuvStr);
            for (int i=0; i<this.getHeight(); i++){
                for (int j=0; j<this.getWidth(); j++){
                    yuvStr = (image[i][j].getY() + " " +
                            image[i][j].getU() + " " +
                            image[i][j].getV()) + "\n";

                    writer.write(yuvStr);
                }
            }

            writer.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void equalize(){
        Histogram histogram = new Histogram(this);
        histogram.equalize();

        for (int i=0; i<height; i++){
            for (int j=0; j<width; j++){
                image[i][j].setY(histogram.getEqualizedLuminocity(image[i][j].getY()));
            }
        }
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    public YUVPixel[][] getImage() {
        return image;
    }

    public void setWidth(int width) {
        this.width = width;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    public void setImage(){
        image = new YUVPixel[height][width];
    }
}
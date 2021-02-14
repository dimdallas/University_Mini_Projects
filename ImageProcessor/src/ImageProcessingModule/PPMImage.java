package ImageProcessingModule;

import java.io.*;
import java.util.Scanner;

public class PPMImage extends RGBImage {

    private File ppmFile;

    public PPMImage(RGBImage img){
        super(img);
    }

    public PPMImage(File file) throws UnsupportedFileFormatException, FileNotFoundException{
       super(0,0,0);
        ppmFile=file;

        Scanner sc = new Scanner(new File(String.valueOf(file)));

        String magicCode = sc.next();
        if(!magicCode.equals("P3")){
            throw new UnsupportedFileFormatException("Wrong magic number");
        }
        int imgWidth=sc.nextInt();
        int imgHeight=sc.nextInt();
        int colorDepth=sc.nextInt();
        if(imgHeight<=0 || imgWidth<=0 || colorDepth<=0){
            throw new UnsupportedFileFormatException("Invalid height/width/colorDepth");
        }
        if(colorDepth>255)
            colorDepth=255;

        this.setHeight(imgHeight);
        this.setWidth(imgWidth);
        this.setColordepth(colorDepth);
        this.setImage();

        int i=0,j=0;
        short red, green, blue;

        RGBPixel[][] thisImg = this.getImage();
        while (sc.hasNextInt()){
            red=(short)sc.nextInt();
            green=(short)sc.nextInt();
            blue= (short)sc.nextInt();
            if (red > colorDepth) {
                red= (short) colorDepth;
            } else if (green > colorDepth) {
                green= (short) colorDepth;
            } else if (blue > colorDepth) {
                blue= (short) colorDepth;
            }
            if(j==imgWidth){
                i++;
                j=0;
            }
            thisImg[i][j]= new RGBPixel(red,green,blue);
            j++;
        }
    }

    public PPMImage(YUVImage img){
        super(img);
    }

    @Override
    public String toString() {
        String ppmStr = "";

        try {
            Scanner sc = new Scanner(new File(String.valueOf(ppmFile)));
            while (sc.hasNext()){
                ppmStr = ppmStr.concat(sc.next() +"\n");
            }
        } catch (FileNotFoundException e) {
           System.out.println("PPM Not Found");
        }
        return ppmStr;
    }

    public void toFile(File file) {
        try {
            file = new File(String.valueOf(file));
            ppmFile=file;
            if (!file.createNewFile()) {
                FileWriter writer = new FileWriter(file);
                writer.write("");
                writer.close();
                System.out.println("File overwritten");
            } else {
                System.out.println("File created");
            }
            FileWriter writer = new FileWriter(file);
            String ppmStr="P3\n" +
                    this.getWidth() + " " + this.getHeight() + "\n" +
                    this.getColorDepth() + "\n";

            writer.write(ppmStr);
            RGBPixel[][] tempImg = this.getImage();
            for (int i=0; i<this.getHeight(); i++){
                for (int j=0; j<this.getWidth(); j++){

                    ppmStr = (tempImg[i][j].getRed() + " " +
                            tempImg[i][j].getGreen() + " " +
                            tempImg[i][j].getBlue());
                    if (j==this.getWidth()-1){
                        ppmStr += "\n";
                    }
                    else
                        ppmStr += " ";
                    writer.write(ppmStr);
                }
            }

            writer.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

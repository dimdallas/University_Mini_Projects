package ImageProcessingModule;

public class RGBImage implements Image {
    public static final int MAX_COLORDEPTH = 255;
    private int width;
    private int height;
    private int colordepth;
    private RGBPixel[][] image;

    public RGBImage(int width, int height, int colordepth) {
        this.width = width;
        this.height = height;

        image = new RGBPixel[this.height][this.width];

        this.colordepth = colordepth;
    }

    public RGBImage(RGBImage copyImg) {
       this.width = copyImg.getWidth();
        this.height = copyImg.getHeight();
        this.colordepth = copyImg.getColorDepth();

        this.image = new RGBPixel[height][width];

        for (int i=0; i<height; i++){
            for (int j=0; j<width; j++){
                image[i][j] = new RGBPixel(copyImg.image[i][j]);
            }
        }
    }

    public RGBImage(YUVImage YUVImg){
        this.width = YUVImg.getWidth();
        this.height = YUVImg.getHeight();
        colordepth = 255;

        this.image = new RGBPixel[height][width];

        for (int i=0; i<height; i++){
            for (int j=0; j<width; j++){
                image[i][j] = new RGBPixel((YUVImg.getImage())[i][j]);
            }
        }
    }

    @Override
    public void grayscale() {
        short grayTemp;
        short redTemp;
        short greenTemp;
        short blueTemp;

        for (int i=0; i<height; i++){
            for (int j=0; j<width; j++){
                blueTemp = image[i][j].getBlue();
                greenTemp = image[i][j].getGreen();
                redTemp = image[i][j].getRed();

                grayTemp = (short) (redTemp*0.3 + greenTemp*0.59 + blueTemp*0.11);
                image[i][j].setBlue(grayTemp);
                image[i][j].setGreen(grayTemp);
                image[i][j].setRed(grayTemp);
            }
        }
    }

    @Override
    public void doublesize() {
        RGBPixel[][] newImg = new RGBPixel[2*height][2*width];
        for (int i=0; i<2*height; i++) {
            for (int j = 0; j <2* width; j++) {
                newImg[i][j]= new RGBPixel((short)0,(short)0,(short)0);
            }
        }
        for (int i=0; i<height; i++){
            for (int j=0; j<width; j++){
                newImg[2*i][2*j].setRGB(image[i][j].getRGB());
                newImg[2*i+1][2*j].setRGB(image[i][j].getRGB());
                newImg[2*i][2*j+1].setRGB(image[i][j].getRGB());
                newImg[2*i+1][2*j+1].setRGB(image[i][j].getRGB());
            }
        }

        width = 2*width;
        height = 2*height;
        image = newImg;
    }

    @Override
    public void halfsize() {
        RGBPixel[][] newImg = new RGBPixel[height/2][width/2];
        int newRed;
        int newGreen;
        int newBlue;

        for (int i=0; i<height/2; i++) {
            for (int j = 0; j <width/2; j++) {
                newImg[i][j]= new RGBPixel((short)0,(short)0,(short)0);
            }
        }


        for (int i=0; i<height/2; i++){
            for (int j=0; j<width/2; j++){
                newRed = ((image[2*i][2*j].getRed() +
                        image[2*i+1][2*j].getRed() +
                        image[2*i][2*j+1].getRed() +
                        image[2*i+1][2*j+1].getRed()))/4;
                newGreen = ((image[2*i][2*j].getGreen() +
                        image[2*i+1][2*j].getGreen() +
                        image[2*i][2*j+1].getGreen() +
                        image[2*i+1][2*j+1].getGreen()))/4;
                newBlue = ((image[2*i][2*j].getBlue() +
                        image[2*i+1][2*j].getBlue() +
                        image[2*i][2*j+1].getBlue() +
                        image[2*i+1][2*j+1].getBlue()))/4;

                newImg[i][j].setRed((short) newRed);
                newImg[i][j].setGreen((short) newGreen);
                newImg[i][j].setBlue((short) newBlue);
            }
        }

        width = width/2;
        height = height/2;
        image = newImg;
    }

    @Override
    public void rotateClockwise() {
        RGBPixel[][] newImg = new RGBPixel[width][height];

        for (int i=0; i<width; i++) {
            for (int j = 0; j <height; j++) {
                newImg[i][j]= new RGBPixel((short)0,(short)0,(short)0);
            }
        }

        int k;
        for (int j=0; j<width; j++){
            k = height-1;
            for (int i=0; i<height; i++, k--){
                newImg[j][k].setRGB(image[i][j].getRGB());
            }
        }

        int temp = width;
        width = height;
        height = temp;
        image = newImg;
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    public int getColorDepth() {
        return colordepth;
    }

    public RGBPixel[][] getImage() {
        return image;
    }

    public RGBPixel getPixel(int row, int col){
        return image[row][col];
    }

    public void setWidth(int width) {
        this.width = width;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    public void setColordepth(int colordepth) {
        this.colordepth = colordepth;
    }

    public void setImage(){
        image = new RGBPixel[this.height][this.width];
    }

    void setPixel(int row, int col, RGBPixel pixel){
        image[row][col] = new RGBPixel(pixel);
    }
}

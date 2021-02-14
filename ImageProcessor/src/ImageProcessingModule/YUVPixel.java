package ImageProcessingModule;

public class YUVPixel {
    private int color;

    public YUVPixel(short y, short u, short v) {
        createColor(y,u,v);
    }

    public YUVPixel(YUVPixel pixel){
        createColor(pixel.getY(),pixel.getU(),pixel.getV());
    }

    public YUVPixel(RGBPixel pixel){
        short Y,U,V;
        Y=(short)(( (  66 * pixel.getRed() + 129 * pixel.getGreen() +  25 * pixel.getBlue() + 128) >> 8) +  16);
        this.setY(Y);
        U= (short)(( ( -38 * pixel.getRed() -  74 * pixel.getGreen() + 112 * pixel.getBlue() + 128) >> 8) + 128);
        this.setU(U);
        V=(short) (( ( 112 * pixel.getRed() -  94 * pixel.getGreen() -  18 * pixel.getBlue() + 128) >> 8) + 128);
        this.setV(V);
    }

    private void createColor(short Y,short U,short V){
        color=0;
        color = color + Y;
        color = color<<8;
        color = color + U;
        color = color<<8;
        color = color + V;
    }

    public short getY() {
        int lsb = 0x000000FF;

        return (short) ((color>>16) & lsb);
    }

    public short getU() {
        int lsb = 0x000000FF;
        return (short) ((color>>8) & lsb);
    }

    public short getV() {
        int lsb = 0x000000FF;
        return (short) (color & lsb);
    }

    public void setY(short y) {
        createColor(y, getU(), getV());
    }

    public void setU(short u) {
        createColor(getY(), u, getV());
    }

    public void setV(short v) {
        createColor(getY(), getU(), v);
    }
    public int getYUV() {
        return color;
    }

    public void setYUV(int color) {
        this.color = color;
    }

}
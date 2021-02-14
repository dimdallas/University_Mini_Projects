package ImageProcessingModule;

public class RGBPixel {
    private int color;

    public RGBPixel(short red, short green, short blue) {
        setRGB(red, green, blue);
    }
    public RGBPixel(RGBPixel pixel){
        setRGB(pixel.getRed(), pixel.getGreen(), pixel.getBlue());
    }

    public RGBPixel(YUVPixel pixel){
        short C,D,E;
        short R,G,B;
        C=(short) (pixel.getY()-16);
        D=(short)(pixel.getU() - 128);
        E=(short)(pixel.getV()-128);

        R=clip(( 298 * C+ 409 * E + 128) >> 8);
        G=clip(( 298 * C - 100 * D - 208 * E + 128) >> 8);
        B = clip(( 298 * C + 516 * D + 128) >> 8);
        this.setRed(R);
        this.setGreen(G);
        this.setBlue(B);
    }
    public short clip(int color){
        if(color<0){
            color=0;
        }else if(color>255){
            color=255;
        }
        return (short) color;
    }

    public short getRed() {
        int lsb = 0x000000FF;
        return (short) ((color>>16) & lsb);
    }

    public short getGreen() {
        int lsb = 0x000000FF;
        return (short) ((color>>8) & lsb);
    }

    public short getBlue() {
        int lsb = 0x000000FF;
        return (short) (color & lsb);
    }

    public void setRed(short red) {
        setRGB(red, getGreen(), getBlue());
    }

    public void setGreen(short green) {
        setRGB(getRed(), green, getBlue());
    }

    public void setBlue(short blue) {
        setRGB(getRed(), getGreen(), blue);
    }

    public int getRGB() {
        return color;
    }

    public void setRGB(int color) {
        this.color = color;
    }

    public final void setRGB(short red, short green, short blue){
        color=0;
        color = color + red;
        color = color<<8;
        color = color + green;
        color = color<<8;
        color = color + blue;
    }

    @Override
    public String toString() {
        return "("+getRed()+","+getGreen()+","+getBlue()+")";
    }
}

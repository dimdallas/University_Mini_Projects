package ImageProcessingModule;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.LinkedList;
import java.util.List;

public class PPMImageStacker {
    private List<PPMImage> stackList;
    private PPMImage stackedPPMImage;

    public PPMImageStacker(File dir) throws FileNotFoundException, UnsupportedFileFormatException {
        if(!dir.exists()){
            throw new FileNotFoundException("[ERROR] Directory <"+dir+"> does not exist!");
        }
        else if (!(dir.isDirectory())){
            throw new UnsupportedFileFormatException("[ERROR] Directory <"+dir+"> is not a directory!");
        }

        stackList = new LinkedList<>();
        File files[] = dir.listFiles();
        if(dir.listFiles()==null || !dir.exists()){
            throw new FileNotFoundException("Directory empty / not found");
        }
        for (File f : files) {
            PPMImage currImg = new PPMImage(new File(String.valueOf(f)));
            stackList.add(currImg);
        }
    }

    public List<PPMImage> getStackList() {
        return stackList;
    }

    public void stack(){
        short red=0,blue=0,green=0;
        stackedPPMImage = new PPMImage(stackList.get(0));

        for(int i=0;i<stackList.get(0).getHeight();i++){
            for(int j=0;j<stackList.get(0).getWidth();j++){
                for(int k=0;k<stackList.size();k++){
                    red = (short) (red + stackList.get(k).getImage()[i][j].getRed());
                    blue = (short) (blue + stackList.get(k).getImage()[i][j].getBlue());
                    green = (short) (green + stackList.get(k).getImage()[i][j].getGreen());
                }
                red=(short)(red/stackList.size());
                blue=(short)(blue/stackList.size());
                green=(short)(green/stackList.size());
                stackedPPMImage.getImage()[i][j].setRed(red);
                stackedPPMImage.getImage()[i][j].setBlue(blue);
                stackedPPMImage.getImage()[i][j].setGreen(green);
                red=0;
                blue=0;
                green=0;
            }
        }
    }

    public PPMImage getStackedImage(){
        return this.stackedPPMImage;
    }
}

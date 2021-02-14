package ImageProcessingModule;

public class UnsupportedFileFormatException extends Exception{
    private String message;

    public UnsupportedFileFormatException() {
    }

    public UnsupportedFileFormatException(String message) {
        this.message = message;
    }



    @Override
    public String getMessage(){
        return this.message;
    }

}

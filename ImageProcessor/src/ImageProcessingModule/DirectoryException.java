package ImageProcessingModule;

public class DirectoryException extends Exception{
    private String msg;

    public DirectoryException (String msg){
        this.msg = msg;
    }

    @Override
    public String getMessage(){
        return this.msg;
    }
}

import java.util.*;
import java.rmi.*;

public class ClientDispatcher implements Dispatcher{
    private View cv = null;
    public ClientDispatcher(){
        this.cv = new ClientView();
    }
    public View dispatch(){
        return this.cv;
    }
}
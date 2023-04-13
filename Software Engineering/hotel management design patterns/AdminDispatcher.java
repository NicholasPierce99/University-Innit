import java.util.*;
import java.rmi.*;

public class AdminDispatcher implements Dispatcher{
    private View av = null;
    public AdminDispatcher(){
        this.av = new AdminView();
    }
    public View dispatch(){
        return this.av;
    }
}
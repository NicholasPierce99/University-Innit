import java.util.*;
import java.rmi.*;

public class StaffDispatcher implements Dispatcher{
    private View sv = null;
    public StaffDispatcher(){
        this.sv = new StaffView();
    }
    public View dispatch(){
        return this.sv;
    }
}
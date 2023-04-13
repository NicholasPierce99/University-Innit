import java.util.*;

public class DispatcherFactory implements HotelAbstractFactory<Dispatcher>{
    Dispatcher d = null;
    public DispatcherFactory(){

    }
    public Dispatcher create_product(String type){
        if (type.equals("admin")){
            d = new AdminDispatcher();
            return d;
        }
        else if(type.equals("staff")){
            d = new StaffDispatcher();
            return d;
        }
        else{
            d = new ClientDispatcher();
            return d;
        }
    }
}
import java.util.*;
import java.rmi.*;

public class StaffView implements View {
    private HotelManagementInterface rh_stub = null;
    private AccountDatabaseInterface db_stub = null;
    StaffView(){
        try{
             rh_stub = (HotelManagementInterface)Naming.lookup("//in-csci-rrpc02:5697/RemoteHotel");
            db_stub = (AccountDatabaseInterface)Naming.lookup("//in-csci-rrpc02:5697/AccountDatabase");
        }
        catch(Exception e){

        }
    }
    public void view(){
        try{
           System.out.println("0: Make Hotel Changes");
            rh_stub.make_hotel_changes();

            //do other admin things
        }
        catch(Exception e){
            
        }
    }
}
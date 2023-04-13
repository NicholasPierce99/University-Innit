import java.util.*;
import java.rmi.*;


public class ClientView implements View{
    private HotelManagementInterface rh_stub = null;
    private AccountDatabaseInterface db_stub = null;
    ClientView(){
        try{
             rh_stub = (HotelManagementInterface)Naming.lookup("//in-csci-rrpc02:5697/RemoteHotel");
            db_stub = (AccountDatabaseInterface)Naming.lookup("//in-csci-rrpc02:5697/AccountDatabase");
        }
        catch(Exception e){

        }
    }
    public void view(){
        try{
            System.out.println("Options: \n 0: Make Reservations \n 1:Cancellations \n 2: Modifications ");
            //based on selection, call client function
            System.out.println("Available rooms, pick a room and make a selection");
            rh_stub.view_hotel();
        }
        catch(Exception e){

        }
    }
}
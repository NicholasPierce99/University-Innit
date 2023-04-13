import java.util.*;
import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;

public class HotelImpl extends UnicastRemoteObject implements HotelManagementInterface{
    private ArrayList<Account> accounts;
    private ArrayList<HotelRoom> rooms;
    public Hotel hot;
    HotelImpl(Hotel hot, AccountDatabase ad) throws RemoteException{
        super();
        this.hot = hot;
        this.rooms = hot.get_hotel();
        try{
            AccountDatabase temp = ad;
            this.accounts = ad.get_accounts();
        }
        catch(Exception e){
                System.out.println(e);
        }
    }
   public void view_hotel() throws RemoteException{
       hot.show_rooms();
   }
   public void make_hotel_changes() throws RemoteException{
       System.out.println("Please select a room to change");
       hot.show_rooms();
       //with the data of the rooms, I can make a simple function to change room content
       //using dummy code right now just to show functionality
   }
   //view/edit dummy
   public void view_accounts() throws RemoteException{
       for(Account x: accounts){
           System.out.println(x.get_username());
       }
   }
}
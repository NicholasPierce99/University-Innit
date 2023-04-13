//remote hotel server class
import java.rmi.*;
import java.util.*;
import java.rmi.registry.*;  

public class RemoteHotel{
    public static void main(String [] args){
        Hotel hotel = new Hotel();
        AccountDatabase ad;
        HotelImpl remote_hotel;

        try{
            System.out.println("Connecting to Accounts");
            ad = new AccountDatabase();
            Naming.rebind("//in-csci-rrpc02:5697/AccountDatabase", ad);
            System.out.println("Connecting to Hotel Management");
            remote_hotel = new HotelImpl(hotel, ad);
            Naming.rebind("//in-csci-rrpc02:5697/RemoteHotel", remote_hotel);
        }
        catch(Exception e){
            System.out.println(e);
        }
    }
}
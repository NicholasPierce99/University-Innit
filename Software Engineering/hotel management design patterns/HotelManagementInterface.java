import java.rmi.*; 

//interface to implement remote 
public interface HotelManagementInterface extends Remote{ 
   public void view_hotel() throws RemoteException;
   public void make_hotel_changes() throws RemoteException;
   public void view_accounts() throws RemoteException;
} 
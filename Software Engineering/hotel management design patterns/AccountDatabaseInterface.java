import java.rmi.*; 
import java.util.*;

//interface to implement remote 
public interface AccountDatabaseInterface extends Remote{ 
   public boolean check_account(String username, String password) throws RemoteException;
   public void add_user_account(String username, String password) throws RemoteException;
   public ArrayList<Account> get_accounts() throws RemoteException;
   public void edit_accounts() throws RemoteException;
} 
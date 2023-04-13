//class to create account database
import java.rmi.*;
import java.util.*;
import java.rmi.server.UnicastRemoteObject;
import java.io.*;

public class AccountDatabase extends UnicastRemoteObject implements AccountDatabaseInterface {
    private ArrayList<Account> accounts;

    AccountDatabase() throws RemoteException{
        this.accounts = new ArrayList<Account>();
        Account admin_account = new Account("admin", "1234");
        Account staff_account = new Account("staff", "5678");
        this.accounts.add(admin_account);
        this.accounts.add(staff_account);
    }
    public boolean check_account(String username, String password) throws RemoteException{
       for(Account x: accounts){
           if(x.get_username().equals(username)){
               if(x.get_password().equals(password)){
                   System.out.println("Account Recognized, welcome " + username);
                   return true;
               }
           }
           else{
               System.out.println("Account not found");
           }
       }
       return false;
   }
    public void add_user_account(String username, String password) throws RemoteException{
        ClientAccount temp = new ClientAccount(username, password);
        accounts.add(temp);
    }
    public ArrayList<Account> get_accounts() throws RemoteException{
        return accounts;
    }
    public void edit_accounts() throws RemoteException{

    }
}
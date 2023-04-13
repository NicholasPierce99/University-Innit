import java.util.*;
import java.rmi.*;

public class AdminView implements View {
    private HotelManagementInterface rh_stub = null;
    private AccountDatabaseInterface db_stub = null;
    AdminView(){
        try{
            rh_stub = (HotelManagementInterface)Naming.lookup("//in-csci-rrpc02:5697/RemoteHotel");
            db_stub = (AccountDatabaseInterface)Naming.lookup("//in-csci-rrpc02:5697/AccountDatabase");
        }
        catch(Exception e){
            System.out.println(e);
        }
    }
    public void view(){
        try{

            System.out.println("0: View and Edit database");
            ArrayList<Account> accounts = db_stub.get_accounts();
            for(Account x: accounts){
                System.out.println(x.get_username() + " " + x.get_password());
            }
            System.out.println("Add a new user");
            Scanner scan = new Scanner(System.in);

            String new_username = scan.nextLine();
            String new_password = scan.nextLine();
            db_stub.add_user_account(new_username, new_password);

            //do other admin things
        }
        catch(Exception e){
            System.out.println(e);
        }
    }
}
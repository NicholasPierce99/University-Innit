//driver for hotel
import java.util.*;
import java.rmi.*;

public class HotelDriver{
    public static void main(String [] args){
        boolean running = true;
        DispatcherFactory df = new DispatcherFactory();
        Dispatcher d = null;
        View v = null;
        try{
            while(running){
                System.out.println("Hello, welcome to the hotel, please sign in with username and password or press 0 to exit");
                Scanner scan = new Scanner(System.in);
                String username = scan.nextLine();
                String password = scan.nextLine();
                if(username.equals("0")){
                    running = false;
                }
                else if(username.equals("admin")){
                    d = df.create_product("admin");
                    v = d.dispatch();
                    v.view();
                }
                else if(username.equals("staff")){
                    d = df.create_product("staff");
                    v = d.dispatch();
                    v.view();
                }
                else{
                    d = df.create_product(null);
                    v = d.dispatch();
                    v.view();    
                    
                }
            }
        }
        catch(Exception e){
                System.out.println(e);
        }
    }
}
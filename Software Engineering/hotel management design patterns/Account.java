//class to implement accounts
import java.util.*;
import java.io.*;

public class Account implements Serializable{
    private String username;
    private String password;

    Account(String username, String password){
        this.username = username;
        this.password = password;
    }
    public String get_username(){
        return this.username;
    }
    public String get_password(){
        return this.password;
    }
}
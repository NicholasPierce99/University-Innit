//class Hotel, wrapper for array of hotelrooms
import java.util.*;
import java.io.*;
public class Hotel implements Serializable{
    private ArrayList<HotelRoom> rooms;
    Hotel(){
        rooms = new ArrayList<HotelRoom>();
        populate_rooms();
    }
    //randomly create hotel rooms
    public void populate_rooms(){
        for(int i = 0; i < 10; i++){
            boolean temp;

            if(Math.random() < .5){
                temp = false;
            }
            else{
                temp = true;
            }
            HotelRoom hot = new HotelRoom(i, i, i, temp);
            rooms.add(hot);
        }
    }
    public void show_rooms(){
        for (HotelRoom x: rooms){
            x.show_room();
        }
    }
    public ArrayList<HotelRoom> get_hotel(){
        return rooms;
    }

}
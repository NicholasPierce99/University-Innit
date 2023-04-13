import java.util.*;

//class that defines a hotel room
public class HotelRoom{
    private int num_beds;
    private int room_number;
    private int quality_number;
    private boolean smoking;
    private boolean reserved;
    HotelRoom(int num_beds, int room_number, int quality_number, boolean smoking){
        this.num_beds = num_beds;
        this.room_number = room_number;
        this.quality_number = quality_number;
        this.smoking = smoking;
        this.reserved = false;
    }
    //setters/getters
    public void set_room_number(int num){
        this.room_number = num;
    }
    public int get_room_number(){
        return this.room_number;
    }
    public void set_quality(int num){
        this.quality_number = num;
    }
    public int get_quality(){
        return this.quality_number;
    }
    public void set_smoking_status(boolean bool){
        this.smoking = bool;
    }
    public boolean get_smoking_status(){
        return this.smoking;
    }
    public void set_status(boolean bool){
        this.reserved = bool;
    }
    public boolean is_booked(){
        return this.reserved;
    }
    public void show_room(){
        System.out.println("Room number: " + this.room_number + "\n" + "Number of beds: " + this.num_beds + "\n" + "Quality: " + this.quality_number + "\n" + "Smoking status:" + this.smoking + "\n" + "Reservation Status: " + this.reserved + "\n");
    }
}

//abstract factory class
public interface HotelAbstractFactory<T>{

    public T create_product(String type);
}
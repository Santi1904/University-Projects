package com.example.braguia.model;

import androidx.room.TypeConverter;

import com.example.braguia.model.Objects.Contact;
import com.example.braguia.model.Objects.Edge;
import com.example.braguia.model.Objects.Partner;
import com.example.braguia.model.Objects.Pin;
import com.example.braguia.model.Objects.Social;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.lang.reflect.Type;
import java.util.List;

public class TypeConverter_BraGuia {

    // converter for socials
    @TypeConverter
    public static List<Social> social_fromString(String value) {
        return new Gson().fromJson(value, new TypeToken<List<Social>>() {}.getType());
    }

    @TypeConverter
    public static String social_fromList(List<Social> socials) {
        return new Gson().toJson(socials);
    }

    // converter for contacts

    @TypeConverter
    public static List<Contact> contact_fromString(String value){
        return new Gson().fromJson(value, new TypeToken<List<Contact>>() {}.getType());
    }

    @TypeConverter
    public static String contact_fromList(List<Contact> contacts){
        return new Gson().toJson(contacts);
    }

    // converter for partners

    @TypeConverter
    public static List<Partner> partner_fromString(String value){
        return new Gson().fromJson(value,new TypeToken<List<Partner>>() {}.getType());
    }

    @TypeConverter
    public static String partner_fromList(List<Partner> partners){
        return new Gson().toJson(partners);
    }

    @TypeConverter
    public static List<Edge> edge_fromString(String value) {
        Type listType = new TypeToken<List<Edge>>() {}.getType();
        return new Gson().fromJson(value, listType);
    }

    @TypeConverter
    public static String edge_fromList(List<Edge> edges) {
        Gson gson = new Gson();
        return gson.toJson(edges);
    }

    @TypeConverter
    public static Pin pins_fromString(String value) {
        return new Gson().fromJson(value, Pin.class);
    }

    @TypeConverter
    public static String pins_fromPin(Pin pin) {
        return new Gson().toJson(pin);
    }

}

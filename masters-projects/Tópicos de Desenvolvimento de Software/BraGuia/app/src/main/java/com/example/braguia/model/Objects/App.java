package com.example.braguia.model.Objects;

import androidx.annotation.NonNull;
import androidx.room.ColumnInfo;
import androidx.room.Entity;
import androidx.room.PrimaryKey;
import androidx.room.TypeConverter;
import androidx.room.TypeConverters;

import com.example.braguia.model.TypeConverter_BraGuia;
import com.google.gson.annotations.SerializedName;

import java.io.Serializable;
import java.util.List;


@Entity(tableName = "app")
@TypeConverters({TypeConverter_BraGuia.class})
public class App implements Serializable {

    @PrimaryKey
    @NonNull
    @SerializedName("app_name")
    @ColumnInfo(name = "app_name")
    private String app_name;

    @SerializedName("socials")
    @ColumnInfo(name = "socials")
    private List<Social> socials;

    @SerializedName("contacts")
    @ColumnInfo(name = "contacts")
    private List<Contact> contacts;

    @SerializedName("partners")
    @ColumnInfo(name = "partners")
    private List<Partner> partners;

    @SerializedName("app_desc")
    @ColumnInfo(name = "app_desc")
    private String app_desc;

    @SerializedName("app_landing_page_text")
    @ColumnInfo(name = "app_landing_page_text")
    private String app_landing_page_text;

    public App(String app_name, List<Social> socials, List<Contact> contacts, List<Partner> partners, String app_desc, String app_landing_page_text){
        this.app_name = app_name;
        this.socials = socials;
        this.contacts = contacts;
        this.partners = partners;
        this.app_desc = app_desc;
        this.app_landing_page_text = app_landing_page_text;
    }

    @NonNull
    public String getApp_name() {
        return app_name;
    }

    public List<Social> getSocials() {
        return socials;
    }

    public List<Contact> getContacts() {
        return contacts;
    }

    public List<Partner> getPartners() {
        return partners;
    }

    public String getApp_desc() {
        return app_desc;
    }

    public String getApp_landing_page_text() {
        return app_landing_page_text;
    }
}

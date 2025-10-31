package com.example.braguia.model.Objects;

import android.nfc.tech.NfcA;
import android.text.BoringLayout;

import androidx.annotation.NonNull;
import androidx.room.ColumnInfo;
import androidx.room.Entity;
import androidx.room.Index;
import androidx.room.PrimaryKey;

@Entity(tableName = "user")
public class User {

    @PrimaryKey
    //private int id;
    @NonNull
    @ColumnInfo(name = "username")
    private String username;
    @ColumnInfo(name = "user_type")
    private String user_type;

    @ColumnInfo(name= "last_login")
    private String last_login;

    @ColumnInfo(name= "is_superuser")
    private boolean is_superuser;

    @ColumnInfo(name= "first_name")
    private String first_name;

    @ColumnInfo(name = "last_name")
    private String last_name;

    @ColumnInfo(name= "email")
    private String email;

    @ColumnInfo(name= "is_staff")
    private boolean is_staff;

    @ColumnInfo(name= "is_active")
    private boolean is_active;

    @ColumnInfo(name= "date_joined")
    private String date_joined;


    public User(String username, String user_type, String last_login, boolean is_superuser, String first_name, String last_name, String email, boolean is_staff, boolean is_active, String date_joined){
        this.username = username;
        this.user_type = user_type;
        this.last_login = last_login;
        this.is_superuser = is_superuser;
        this.first_name = first_name;
        this.last_name = last_name;
        this.email = email;
        this.is_staff = is_staff;
        this.is_active = is_active;
        this.date_joined = date_joined;
    }

    public void setUsername(@NonNull String username) {
        this.username = username;
    }

    public void setUser_type(String user_type) {
        this.user_type = user_type;
    }

    public void setLast_login(String last_login) {
        this.last_login = last_login;
    }

    public void setIs_superuser(boolean is_superuser) {
        this.is_superuser = is_superuser;
    }

    public void setFirst_name(String first_name) {
        this.first_name = first_name;
    }

    public void setLast_name(String last_name) {
        this.last_name = last_name;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public void setIs_staff(boolean is_staff) {
        this.is_staff = is_staff;
    }

    public void setIs_active(boolean is_active) {
        this.is_active = is_active;
    }

    public void setDate_joined(String date_joined) {
        this.date_joined = date_joined;
    }

    @NonNull
    public String getUsername() {
        return username;
    }

    public String getUser_type() {
        return user_type;
    }

    public String getLast_login() {
        return last_login;
    }

    public boolean isIs_superuser() {
        return is_superuser;
    }

    public String getFirst_name() {
        return first_name;
    }

    public String getLast_name() {
        return last_name;
    }

    public String getEmail() {
        return email;
    }

    public boolean isIs_staff() {
        return is_staff;
    }

    public boolean isIs_active() {
        return is_active;
    }

    public String getDate_joined() {
        return date_joined;
    }
}

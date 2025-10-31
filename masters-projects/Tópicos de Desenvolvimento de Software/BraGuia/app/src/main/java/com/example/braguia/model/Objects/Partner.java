package com.example.braguia.model.Objects;

import androidx.annotation.NonNull;
import androidx.room.ColumnInfo;
import androidx.room.Entity;
import androidx.room.ForeignKey;
import androidx.room.PrimaryKey;

import com.google.gson.annotations.SerializedName;

import java.io.Serializable;

@Entity(tableName = "partner",
        foreignKeys = @ForeignKey(entity = App.class,parentColumns = "app_name",childColumns = "partner_app",onDelete = ForeignKey.CASCADE))

public class Partner implements Serializable {

    @PrimaryKey
    @NonNull
    @SerializedName("partner_name")
    @ColumnInfo(name = "partner_name")
    private String partner_name;

    @SerializedName("partner_phone")
    @ColumnInfo(name = "partner_phone")
    private String partner_phone;

    @SerializedName("partner_url")
    @ColumnInfo(name = "partner_url")
    private String partner_url;

    @SerializedName("partner_mail")
    @ColumnInfo(name = "partner_mail")
    private String partner_mail;

    @SerializedName("partner_desc")
    @ColumnInfo(name = "partner_desc")
    private String partner_desc;

    @SerializedName("partner_app")
    @ColumnInfo(name = "partner_app")
    private String partner_app;

    @NonNull
    public String getPartner_name() {
        return partner_name;
    }

    public String getPartner_phone() {
        return partner_phone;
    }

    public String getPartner_url() {
        return partner_url;
    }

    public String getPartner_mail() {
        return partner_mail;
    }

    public String getPartner_desc() {
        return partner_desc;
    }

    public String getPartner_app() {
        return partner_app;
    }
}

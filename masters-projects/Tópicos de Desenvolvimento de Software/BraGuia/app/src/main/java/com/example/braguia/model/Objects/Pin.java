package com.example.braguia.model.Objects;

import com.google.gson.annotations.SerializedName;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class Pin implements Serializable {

    @SerializedName("id")
    private int id;

    @SerializedName("media")
    private List<Media> media;

    @SerializedName("pin_name")
    private String pin_name;

    @SerializedName("pin_desc")
    private String pin_desc;

    @SerializedName("pin_lat")
    private Double pin_lat;

    @SerializedName("pin_lng")
    private Double pin_lng;

    @SerializedName("pin_alt")
    private Double pin_alt;

    public Pin() {
        this.id = -1;
        this.media = new ArrayList<>();
        this.pin_name = "";
        this.pin_desc = "";
        this.pin_lat = 0.0;
        this.pin_lng = 0.0;
        this.pin_alt = 0.0;
    }

    public Pin(int id, List<Media> media, String pin_name, String pin_desc, Double pin_lat, Double pin_lng, Double pin_alt) {
        this.id = id;
        this.media = media;
        this.pin_name = pin_name;
        this.pin_desc = pin_desc;
        this.pin_lat = pin_lat;
        this.pin_lng = pin_lng;
        this.pin_alt = pin_alt;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public List<Media> getMedia() {
        return media;
    }

    public void setMedia(List<Media> media) {
        this.media = media;
    }

    public String getPin_name() {
        return pin_name;
    }

    public void setPin_name(String pin_name) {
        this.pin_name = pin_name;
    }

    public String getPin_desc() {
        return pin_desc;
    }

    public void setPin_desc(String pin_desc) {
        this.pin_desc = pin_desc;
    }

    public Double getPin_lat() {
        return pin_lat;
    }

    public void setPin_lat(Double pin_lat) {
        this.pin_lat = pin_lat;
    }

    public Double getPin_lng() {
        return pin_lng;
    }

    public void setPin_lng(Double pin_lng) {
        this.pin_lng = pin_lng;
    }

    public Double getPin_alt() {
        return pin_alt;
    }

    public void setPin_alt(Double pin_alt) {
        this.pin_alt = pin_alt;
    }
}

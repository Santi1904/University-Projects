package com.example.braguia.model.Objects;

import androidx.annotation.NonNull;
import androidx.room.ColumnInfo;
import androidx.room.Entity;
import androidx.room.Ignore;
import androidx.room.Index;
import androidx.room.PrimaryKey;
import androidx.room.TypeConverters;

import com.example.braguia.model.TypeConverter_BraGuia;
import com.google.gson.annotations.SerializedName;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

@Entity(tableName = "trail",indices = @Index(value = {"id"},unique = true))
@TypeConverters({TypeConverter_BraGuia.class})
public class Trail implements Serializable {

    @PrimaryKey
    @NonNull
    @SerializedName("id")
    @ColumnInfo(name = "id")
    private int id;

    @SerializedName("trail_img")
    @ColumnInfo(name = "trail_img")
    private String trail_img;

    @SerializedName("edges")
    private List<Edge> edges;

    @SerializedName("trail_name")
    @ColumnInfo(name = "trail_name")
    private String trail_name;

    @SerializedName("trail_desc")
    @ColumnInfo(name = "trail_desc")
    private String trail_desc;

    @SerializedName("trail_duration")
    @ColumnInfo(name = "trail_duration")
    private int trail_duration;

    @SerializedName("trail_difficulty")
    @ColumnInfo(name = "trail_difficulty")
    private String trail_difficulty;

    public Trail() {
        this.id = -1;
        this.trail_img = "";
        this.edges = new ArrayList<>();
        this.trail_name = "";
        this.trail_desc = "";
        this.trail_duration = 0;
        this.trail_difficulty = "";
    }

    public Trail(int id, String trail_img, List<Edge> edges, String trail_name, String trail_desc, int trail_duration, String trail_difficulty) {
        this.id = id;
        this.trail_img = trail_img;
        this.edges = new ArrayList<>(edges);
        this.trail_name = trail_name;
        this.trail_desc = trail_desc;
        this.trail_duration = trail_duration;
        this.trail_difficulty = trail_difficulty;
    }

    @NonNull
    public int getId() {
        return id;
    }

    public void setId(@NonNull int id) {
        this.id = id;
    }

    public String getTrail_img() {
        return trail_img;
    }

    public void setTrail_img(String trail_img) {
        this.trail_img = trail_img;
    }

    public List<Edge> getEdges() {
        return edges;
    }

    public void setEdges(List<Edge> edges) {
        this.edges = edges;
    }

    public String getTrail_name() {
        return trail_name;
    }

    public void setTrail_name(String trail_name) {
        this.trail_name = trail_name;
    }

    public String getTrail_desc() {
        return trail_desc;
    }

    public void setTrail_desc(String trail_desc) {
        this.trail_desc = trail_desc;
    }

    public int getTrail_duration() {
        return trail_duration;
    }

    public void setTrail_duration(int trail_duration) {
        this.trail_duration = trail_duration;
    }

    public String getTrail_difficulty() {
        return trail_difficulty;
    }

    public void setTrail_difficulty(String trail_difficulty) {
        this.trail_difficulty = trail_difficulty;
    }

    public boolean equals(Trail t){
        return (this.id == t.getId()) && (this.getTrail_img().equals(t.getTrail_img())) && (this.trail_name.equals(t.getTrail_name())) && (this.trail_desc.equals(t.getTrail_desc())) && (this.trail_duration == t.getTrail_duration()) && (this.trail_difficulty.equals(t.getTrail_difficulty()));
    }

    // TODO: toString(Trail trail)
}

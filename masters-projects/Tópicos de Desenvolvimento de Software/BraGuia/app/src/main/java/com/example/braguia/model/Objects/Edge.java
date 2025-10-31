package com.example.braguia.model.Objects;

import androidx.room.ColumnInfo;
import androidx.room.Entity;
import androidx.room.ForeignKey;
import androidx.room.Index;
import androidx.room.PrimaryKey;
import androidx.room.TypeConverters;

import com.example.braguia.model.TypeConverter_BraGuia;
import com.google.gson.annotations.SerializedName;

import java.io.Serializable;


@Entity(
        tableName = "edge",
        foreignKeys = @ForeignKey(
                entity = Trail.class,
                parentColumns = "id",
                childColumns = "edge_trail",
                onDelete = ForeignKey.CASCADE
        ),
        indices = {
                @Index(value = {"id"}, unique = true),
                @Index(value = {"edge_start"}, unique = true),
                @Index(value = {"edge_end"}, unique = true)
        })
@TypeConverters({TypeConverter_BraGuia.class})
public class Edge implements Serializable {

    @PrimaryKey
    @ColumnInfo(name = "id")
    @SerializedName("id")
    private int id;

    @ColumnInfo(name = "edge_start")
    @SerializedName("edge_start")
    private Pin edge_start;

    @ColumnInfo(name = "edge_end")
    @SerializedName("edge_end")
    private Pin edge_end;

    @ColumnInfo(name = "edge_transport")
    @SerializedName("edge_transport")
    private String edge_transport;

    @ColumnInfo(name = "edge_duration")
    @SerializedName("edge_duration")
    private int edge_duration;

    @ColumnInfo(name = "edge_desc")
    @SerializedName("edge_desc")
    private String edge_desc;

    @ColumnInfo(name = "edge_trail")
    @SerializedName("edge_trail")
    private int edge_trail;

    public Edge() {
        this.id = -1;
        this.edge_start = new Pin();
        this.edge_end = new Pin();
        this.edge_transport = "";
        this.edge_duration = 0;
        this.edge_desc = "";
        this.edge_trail = -1;
    }

    public Edge(int id, Pin edge_start, Pin edge_end, String edge_transport, int edge_duration, String edge_desc, int edge_trail) {
        this.id = id;
        this.edge_start = edge_start;
        this.edge_end = edge_end;
        this.edge_transport = edge_transport;
        this.edge_duration = edge_duration;
        this.edge_desc = edge_desc;
        this.edge_trail = edge_trail;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public Pin getEdge_start() {
        return edge_start;
    }

    public void setEdge_start(Pin edge_start) {
        this.edge_start = edge_start;
    }

    public Pin getEdge_end() {
        return edge_end;
    }

    public void setEdge_end(Pin edge_end) {
        this.edge_end = edge_end;
    }

    public String getEdge_transport() {
        return edge_transport;
    }

    public void setEdge_transport(String edge_transport) {
        this.edge_transport = edge_transport;
    }

    public int getEdge_duration() {
        return edge_duration;
    }

    public void setEdge_duration(int edge_duration) {
        this.edge_duration = edge_duration;
    }

    public String getEdge_desc() {
        return edge_desc;
    }

    public void setEdge_desc(String edge_desc) {
        this.edge_desc = edge_desc;
    }

    public int getEdge_trail() {
        return edge_trail;
    }

    public void setEdge_trail(int edge_trail) {
        this.edge_trail = edge_trail;
    }
}

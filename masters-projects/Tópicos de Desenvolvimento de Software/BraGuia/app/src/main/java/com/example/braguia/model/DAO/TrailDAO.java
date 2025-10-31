package com.example.braguia.model.DAO;

import androidx.lifecycle.LiveData;
import androidx.room.Dao;
import androidx.room.Insert;
import androidx.room.OnConflictStrategy;
import androidx.room.Query;

import com.example.braguia.model.Objects.Trail;

import java.util.List;

@Dao
public interface TrailDAO {
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    void insert(List<Trail> trails);

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    void insertOne(Trail trail);

    @Query("SELECT DISTINCT * FROM trail")
    LiveData<List<Trail>> getAllTrails();

    @Query("SELECT * FROM trail WHERE id = :id")
    LiveData<Trail> getTrailById(int id);

    @Query("DELETE FROM trail")
    void deleteAll();
}

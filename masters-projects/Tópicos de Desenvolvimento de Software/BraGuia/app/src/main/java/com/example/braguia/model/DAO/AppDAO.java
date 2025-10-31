package com.example.braguia.model.DAO;

import androidx.lifecycle.LiveData;
import androidx.room.Dao;
import androidx.room.Delete;
import androidx.room.Insert;
import androidx.room.OnConflictStrategy;
import androidx.room.Query;

import com.example.braguia.model.Objects.App;
import com.example.braguia.model.Objects.User;

import java.util.List;

@Dao
public interface AppDAO {

    @Insert(onConflict = OnConflictStrategy.IGNORE)
    void insert(App app);

    @Query("SELECT * FROM app")
    LiveData<App> getAll();

    @Query("DELETE FROM app")
    void deleteAll();
}

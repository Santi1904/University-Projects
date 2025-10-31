package com.example.braguia.model;

import android.content.Context;

import androidx.annotation.NonNull;
import androidx.room.Database;
import androidx.room.Room;
import androidx.room.RoomDatabase;
import androidx.sqlite.db.SupportSQLiteDatabase;

import com.example.braguia.model.DAO.AppDAO;
import com.example.braguia.model.DAO.TrailDAO;
import com.example.braguia.model.DAO.UserDAO;
import com.example.braguia.model.Objects.App;
import com.example.braguia.model.Objects.Edge;
import com.example.braguia.model.Objects.Trail;
import com.example.braguia.model.Objects.User;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

@Database(entities= {Trail.class, Edge.class, User.class, App.class}, version=3, exportSchema = false)
public abstract class BraguiaDatabase extends RoomDatabase {

    private static final String DATABASE_NAME = "Braguia";

    public abstract UserDAO userDAO();

    public abstract TrailDAO trailDAO();

    public abstract AppDAO appDAO();

    private static volatile BraguiaDatabase INSTANCE = null;

    private static final int NUMBER_OF_THREADS = 4;
    public static final ExecutorService databaseWriteExecutor =
            Executors.newFixedThreadPool(NUMBER_OF_THREADS);

    public static BraguiaDatabase getInstance(Context context){

        if (INSTANCE == null){
            synchronized (BraguiaDatabase.class){
                if (INSTANCE == null){
                    INSTANCE = Room.databaseBuilder(context.getApplicationContext(),BraguiaDatabase.class,DATABASE_NAME)
                            .fallbackToDestructiveMigration()
                            .build();
                }
            }
        }
        return INSTANCE;
    }

    public static Callback callback = new Callback() {
        @Override
        public void onOpen(@NonNull SupportSQLiteDatabase db) {
            super.onOpen(db);
            populateDbAsync(INSTANCE);
        }
    };

    public static final ExecutorService executorService = Executors.newFixedThreadPool(4);

    public static void populateDbAsync(BraguiaDatabase catDatabase) {
        executorService.execute(() -> {
            UserDAO userDAO = catDatabase.userDAO();
            TrailDAO trailDAO = catDatabase.trailDAO();
            AppDAO appDAO = catDatabase.appDAO();

            userDAO.deleteAll();
            trailDAO.deleteAll();
            appDAO.deleteAll();
        });
    }

//    static class PopulateDbAsyn extends AsyncTask<Void,Void,Void>{
//
//        private UserDAO userDAO;
//        private TrailDAO trailDAO;
//
//        public PopulateDbAsyn(BraguiaDatabase catDatabase){
//            userDAO = catDatabase.userDAO();
//            trailDAO = catDatabase.trailDAO();
//        }
//
//        @Override
//        protected Void doInBackground(Void... voids){
//            userDAO.deleteAll();
//            return null;
//        }
//    }
}

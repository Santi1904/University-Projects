package com.example.braguia.repository;

import android.app.Application;
import android.content.Context;
import android.util.Log;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;

import com.example.braguia.BuildConfig;
import com.example.braguia.model.API_service;
import com.example.braguia.model.BraguiaDatabase;
import com.example.braguia.model.DAO.AppDAO;
import com.example.braguia.model.Objects.App;
import com.google.gson.internal.GsonBuildConfig;

import java.util.List;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;

public class AppRepository {

    private static final String BACKEND_URL = BuildConfig.BRAGUIA_API_URL;
    public AppDAO appDAO;
    public LiveData<App> app;
    API_service app_api;



    public AppRepository(Application application) {

        BraguiaDatabase db = BraguiaDatabase.getInstance(application);
        appDAO = db.appDAO();
        app = appDAO.getAll();

        Retrofit retrofit = new Retrofit.Builder()
                .baseUrl(BACKEND_URL)
                .addConverterFactory(GsonConverterFactory.create())
                .build();

        app_api = retrofit.create(API_service.class);
        getAppAPI();
    }

    public void insert(App app){
        BraguiaDatabase.databaseWriteExecutor.execute(() -> {
            appDAO.insert(app);
        });
    }

    public LiveData<App> getApp(){
        return appDAO.getAll();
    }

    public void getAppAPI(){

        Call<List<App>> call = app_api.getApp();
        call.enqueue(new Callback<List<App>>() {
            @Override
            public void onResponse(Call<List<App>> call, Response<List<App>> response) {

                if (response.isSuccessful()){

                    insert(response.body().get(0));
                }
                else{
                    System.out.println("ERRO ERRO ERRO");
                }
            }

            @Override
            public void onFailure(Call<List<App>> call, Throwable t) {
                Log.e("main", "onFailure: " + t.getMessage());
                Log.e("main", "message: " + t.getCause());
            }
        });
    }
}

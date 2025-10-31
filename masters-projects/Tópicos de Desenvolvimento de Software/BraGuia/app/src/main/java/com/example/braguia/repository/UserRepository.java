package com.example.braguia.repository;

import android.app.Application;
import android.content.Context;
import android.content.SharedPreferences;
import android.util.Log;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;

import com.example.braguia.BuildConfig;
import com.example.braguia.model.API_service;
import com.example.braguia.model.BraguiaDatabase;
import com.example.braguia.model.Objects.User;
import com.example.braguia.model.DAO.UserDAO;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Locale;
import java.util.TimeZone;

import okhttp3.ResponseBody;
import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;

public class UserRepository {

    private UserDAO userDAO;
    private LiveData<List<User>> users;
    private String liveUser;
    private MutableLiveData<Boolean> loginResult;
    private MutableLiveData<Boolean> logoutResult;

    SharedPreferences sharedPreferences;

    private static final String BACKEND_URL = BuildConfig.BRAGUIA_API_URL;

    API_service user_api;

    public UserRepository(Application application) {

        BraguiaDatabase db = BraguiaDatabase.getInstance(application);
        userDAO = db.userDAO();
        users = userDAO.getAll();

        Retrofit retrofit = new Retrofit.Builder()
                .baseUrl(BACKEND_URL)
                .addConverterFactory(GsonConverterFactory.create())
                .build();

        user_api = retrofit.create(API_service.class);
        sharedPreferences = application.getApplicationContext().getSharedPreferences("BraguiaData", Context.MODE_PRIVATE);
        loginResult = new MutableLiveData<>();
        logoutResult = new MutableLiveData<>();

    }

    public LiveData<List<User>> getAllUsers() {
        return users;
    }

    public void insert(User user) {
        BraguiaDatabase.databaseWriteExecutor.execute(() -> {
            userDAO.insert(user);
        });
    }

    public LiveData<User> getUser() {
        String username = sharedPreferences.getString("liveUser", "");
        return userDAO.findByName(username);
    }

    public void loginAPI(String username, String password) {

        SharedPreferences.Editor editor = sharedPreferences.edit();
        Call<ResponseBody> loginCall = user_api.login(username, password);

        loginCall.enqueue(new Callback<ResponseBody>() {
            @Override
            public void onResponse(Call<ResponseBody> call, Response<ResponseBody> response) {

                if (response.isSuccessful()) {

                    List<String> formatted_cookies = new ArrayList<>();
                    List<String> cookiesExpireDate = new ArrayList<>();
                    List<String> api_cookies = response.headers().values("Set-Cookie");

                    for (String header : api_cookies) {

                        String cookie = header.split(";")[0];
                        formatted_cookies.add(cookie);

                        String expireDate = header.split("expires=")[1].split(";")[0];
                        cookiesExpireDate.add(expireDate);


                    }

                    if (!formatted_cookies.isEmpty()) {
                        editor.putString("csrftoken", formatted_cookies.get(0));
                        editor.putString("sessionid", formatted_cookies.get(1));
                        editor.apply();
                    }

                    if(!cookiesExpireDate.isEmpty()){
                        editor.putString("csrfExpire", cookiesExpireDate.get(0));
                        editor.putString("sessionExpire", cookiesExpireDate.get(1));
                        editor.apply();
                    }

                    loginResult.setValue(true);
                    getUserAPI();
                } else {
                    loginResult.setValue(false);
                }
            }

            @Override
            public void onFailure(Call<ResponseBody> call, Throwable t) {

                Log.e("main", "onFailure: " + t.getMessage());
                Log.e("main", "message: " + t.getCause());

            }
        });
    }

    public LiveData<Boolean> getLoginStatus() {
        return loginResult;
    }

    public LiveData<Boolean> getLogoutStatus() {
        return logoutResult;
    }

    public String getCookieExpire(){

        return sharedPreferences.getString("sessionExpire","");
    }


    public void getUserAPI() {

        String csrftoken = sharedPreferences.getString("csrftoken", "");
        String sessionid = sharedPreferences.getString("sessionid", "");

        if (!csrftoken.isEmpty() && !sessionid.isEmpty()) {
            StringBuilder cookiesAPI = new StringBuilder("");
            cookiesAPI.append(csrftoken).append(";").append(sessionid);

            //System.out.println(cookiesAPI);

            Call<User> call = user_api.getUser(cookiesAPI.toString());
            call.enqueue(new Callback<User>() {
                @Override
                public void onResponse(Call<User> call, Response<User> response) {

                    if (response.isSuccessful()) {
                        User user = response.body();
                        insert(user);
                        liveUser = user.getUsername();
                        if (!liveUser.isEmpty()) {
                            SharedPreferences.Editor editor = sharedPreferences.edit();
                            editor.putString("liveUser", liveUser);
                            editor.apply();
                        }
                    } else {
                        System.out.println(response);
                    }
                }

                @Override
                public void onFailure(Call<User> call, Throwable t) {
                    System.out.println("ERROR");
                    System.out.println(t);
                }
            });
        }
    }

    public void logoutAPI() {

        String csrftoken = sharedPreferences.getString("csrftoken", "");
        String sessionid = sharedPreferences.getString("sessionid", "");

        if (!csrftoken.isEmpty() && !sessionid.isEmpty()) {

            StringBuilder cookiesAPI = new StringBuilder("");
            cookiesAPI.append(csrftoken).append(";").append(sessionid);

            //System.out.println(cookiesAPI);

            Call<User> call = user_api.logout(sessionid);
            call.enqueue(new Callback<User>() {
                @Override
                public void onResponse(Call<User> call, Response<User> response) {

                    if (response.isSuccessful()) {
                        SharedPreferences.Editor editor = sharedPreferences.edit();
                        editor.putString("csrftoken", "");
                        editor.putString("sessionid", "");
                        editor.putString("liveUser", "");
                        editor.putString("sessionExpire","");
                        editor.apply();
                        logoutResult.setValue(true);
                    } else {
                        logoutResult.setValue(false);
                    }
                }

                @Override
                public void onFailure(Call<User> call, Throwable t) {

                    System.out.println("ERROR");
                    System.out.println(t);
                }
            });
        }
    /*
    public class InsertAsyncTask extends AsyncTask<User,Void,Void> {

        private UserDAO userDAO;
        @Override
        protected Void doInBackground(User... users){
            userDAO.insert(users[0]);
            return null;
        }
    }
     */

    }
}

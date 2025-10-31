package com.example.braguia.model;

import com.example.braguia.model.Objects.App;
import com.example.braguia.model.Objects.Trail;
import com.example.braguia.model.Objects.User;

import java.util.List;

import okhttp3.ResponseBody;
import retrofit2.Call;
import retrofit2.http.Field;
import retrofit2.http.FormUrlEncoded;
import retrofit2.http.GET;
import retrofit2.http.Header;
import retrofit2.http.POST;

public interface API_service {

    @GET("user")
    Call<User> getUser(@Header("Cookie") String cookies);

    @FormUrlEncoded
    @POST("login")
    Call<ResponseBody> login(@Field("username") String username, @Field("password") String password);

    @POST("logout")
    Call<User> logout(@Header("sessionid") String cookies);

    @GET("trails")
    Call<List<Trail>> getTrails();

    @GET("app")
    Call<List<App>> getApp();


}

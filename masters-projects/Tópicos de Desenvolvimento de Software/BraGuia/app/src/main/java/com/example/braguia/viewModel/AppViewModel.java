package com.example.braguia.viewModel;

import android.app.Application;

import androidx.lifecycle.AndroidViewModel;
import androidx.lifecycle.LiveData;

import com.example.braguia.model.Objects.App;
import com.example.braguia.model.Objects.User;
import com.example.braguia.repository.AppRepository;
import com.example.braguia.repository.UserRepository;

import java.util.List;

public class AppViewModel extends AndroidViewModel {

    private AppRepository appRepo;
    private final LiveData<App> appLiveData;


    public AppViewModel(Application application) {
        super(application);
        appRepo = new AppRepository(application);
        appLiveData = appRepo.getApp();
    }

    public LiveData<App> getApp(){
        return appLiveData;
    }
}

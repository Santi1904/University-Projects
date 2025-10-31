package com.example.braguia.viewModel;

import android.app.Application;

import androidx.lifecycle.AndroidViewModel;
import androidx.lifecycle.LiveData;

import com.example.braguia.model.Objects.User;
import com.example.braguia.repository.UserRepository;

public class UserViewModel extends AndroidViewModel {

    private UserRepository userRepository;

    private final LiveData<User> userAPI;

    public UserViewModel(Application application) {
        super(application);
        userRepository = new UserRepository(application);
        userAPI = userRepository.getUser();
    }

    public void login(String username, String password) {
        userRepository.loginAPI(username,password);
    }

    public void logout() {
        userRepository.logoutAPI();
    }

    public LiveData<Boolean> getLoginStatus() {
        return userRepository.getLoginStatus();
    }

    public LiveData<User> getUser() {
        return userAPI;
    }

    public LiveData<Boolean> getLogoutStatus() {
        return userRepository.getLogoutStatus();
    }

    public String getCookieExpire() {
        return userRepository.getCookieExpire();
    }

    public void insert(User user) {
        userRepository.insert(user);
    }
}

package com.example.braguia.ui;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.View;
import android.widget.CompoundButton;
import android.widget.ImageButton;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.app.AppCompatDelegate;
import androidx.appcompat.widget.SwitchCompat;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;
import androidx.lifecycle.ViewModelProvider;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.example.braguia.R;
import com.example.braguia.model.Objects.Social;
import com.example.braguia.viewModel.AppViewModel;
import com.example.braguia.viewModel.LocationService;

public class SettingsActivity extends AppCompatActivity {

    private SharedPreferences sharedPreferences;


    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);

        ImageButton go_back = findViewById(R.id.go_back_settings);
        go_back.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                finish();
            }
        });

        SwitchCompat themeSwitch = findViewById(R.id.themeSwitch);
        sharedPreferences = getSharedPreferences("myPrefs", MODE_PRIVATE);
        
        boolean isDarkModeOn = sharedPreferences.getBoolean("darkMode", false);
        themeSwitch.setChecked(isDarkModeOn);

        themeSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                SharedPreferences.Editor editor = sharedPreferences.edit();
                editor.putBoolean("darkMode", isChecked);
                editor.apply();

                if (isChecked) {
                    AppCompatDelegate.setDefaultNightMode(AppCompatDelegate.MODE_NIGHT_YES);
                    recreate();
                } else {
                    AppCompatDelegate.setDefaultNightMode(AppCompatDelegate.MODE_NIGHT_NO);
                    recreate();
                }
            }
        });

        SwitchCompat locSwitch = findViewById(R.id.locSwitch);
        locSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked){
                    Intent serviceIntent = new Intent(SettingsActivity.this, LocationService.class);
                    stopService(serviceIntent);
                    Toast.makeText(SettingsActivity.this ,"Localização em background desativada",Toast.LENGTH_SHORT).show();
                } else{
                    Intent serviceIntent = new Intent(SettingsActivity.this, LocationService.class);
                    startService(serviceIntent);
                    Toast.makeText(SettingsActivity.this ,"Localização em background ativada",Toast.LENGTH_SHORT).show();
                }
            }
        });
    }

    @Override
    public void onPause() {
        super.onPause();
    }

    @Override
    public void onResume() {
        super.onResume();
    }


}


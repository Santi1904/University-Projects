package com.example.braguia.ui;

import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;

import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;
import androidx.lifecycle.ViewModelProvider;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.example.braguia.R;
import com.example.braguia.model.Objects.Partner;
import com.example.braguia.model.Objects.Social;
import com.example.braguia.viewModel.AppViewModel;

public class PartnerActivity extends AppCompatActivity {

    private AppViewModel appViewModel;

    private PartnerRecyclerViewAdapter adapter;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_partners);

        appViewModel = new ViewModelProvider(this).get(AppViewModel.class);

        RecyclerView recyclerView = findViewById(R.id.partners_list);
        recyclerView.setLayoutManager(new LinearLayoutManager(this, LinearLayoutManager.VERTICAL, false));

        appViewModel.getApp().observe(this, app -> {
            adapter = new PartnerRecyclerViewAdapter(app.getPartners(), position -> {
                Partner selectedPartner = app.getPartners().get(position);
                Bundle bundle = new Bundle();
                bundle.putSerializable("selectedPartner", selectedPartner);

                FragmentManager fragmentManager = getSupportFragmentManager();
                FragmentTransaction transaction = fragmentManager.beginTransaction();
                PartnerInfoFragment fragment = new PartnerInfoFragment();
                fragment.setArguments(bundle);
                transaction.replace(android.R.id.content, fragment); // Replace with activity's root container ID
                transaction.addToBackStack(null);
                transaction.commit();
            });
            recyclerView.setAdapter(adapter);
        });

        ImageButton go_back = findViewById(R.id.go_back_partners);
        go_back.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                finish();
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

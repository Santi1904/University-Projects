package com.example.braguia.ui;

import android.content.Intent;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.fragment.app.Fragment;

import com.example.braguia.R;

public class AppFragment extends Fragment {

    private TextView contacts;

    private TextView socials;

    private TextView partners;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        View view = inflater.inflate(R.layout.fragment_app, container, false);

        contacts = view.findViewById(R.id.contactos);
        socials = view.findViewById(R.id.socials);
        partners = view.findViewById(R.id.partners);

        contacts.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(getContext(), ContactActivity.class));
            }
        });

        socials.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(getContext(), SocialActivity.class));
            }
        });

        partners.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(getContext(),PartnerActivity.class));
            }
        });
        //ListView listView = view.findViewById(R.id.list_contacts);

        //appViewModel = new ViewModelProvider(this).get(AppViewModel.class);
        //appViewModel.getApp().observe(getViewLifecycleOwner(),app -> {

            //adapter = new ContactListAdapter(app.getContacts());

        //});
        //listView.setAdapter(adapter);

        return view;
    }
}


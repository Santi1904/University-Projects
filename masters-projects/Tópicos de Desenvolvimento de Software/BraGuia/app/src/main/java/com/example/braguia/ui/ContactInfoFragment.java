package com.example.braguia.ui;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;

import com.example.braguia.R;
import com.example.braguia.model.Objects.Contact;

public class ContactInfoFragment extends Fragment {

    private Contact contact;

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (getArguments() != null) {
            contact = (Contact) getArguments().getSerializable("selectedContact");
        }
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_contact_info, container, false);

        TextView setContactName = view.findViewById(R.id.setContactName);
        TextView setContactPhone = view.findViewById(R.id.setContactPhone);
        TextView setContactLink = view.findViewById(R.id.setContactLink);
        TextView setContactEmail = view.findViewById(R.id.setContactEmail);

       ImageView callNumber = view.findViewById(R.id.callNumber);

       callNumber.setOnClickListener(new View.OnClickListener() {
           @Override
           public void onClick(View v) {
               Intent dialIntent = new Intent(Intent.ACTION_DIAL);
               dialIntent.setData(Uri.parse("tel:" + contact.getContact_phone()));

               // Inicie a intenção
               startActivity(dialIntent);
           }
       });

        if (contact != null){

            setContactName.setText(contact.getContact_name());
            setContactPhone.setText(contact.getContact_phone());
            setContactLink.setText(contact.getContact_url());
            setContactEmail.setText(contact.getContact_mail());

        }

        Button backButton = view.findViewById(R.id.go_back_button);
        backButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FragmentManager fragmentManager = requireActivity().getSupportFragmentManager();
                if (fragmentManager.getBackStackEntryCount() > 0) {
                    fragmentManager.popBackStack();
                }
            }
        });

        return view;
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

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
import com.example.braguia.model.Objects.Social;

public class SocialInfoFragment extends Fragment {

    private Social social;

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (getArguments() != null) {
            social = (Social) getArguments().getSerializable("selectedSocial");
        }
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_social_info, container, false);

        TextView setContactName = view.findViewById(R.id.setSocialName);
        TextView setContactLink = view.findViewById(R.id.setSocialLink);


        ImageView link = view.findViewById(R.id.go_to_link);

        link.setOnClickListener(new View.OnClickListener() {

            @Override
                public void onClick(View v) {


                    Intent intent = new Intent(Intent.ACTION_VIEW);
                    intent.setData(Uri.parse(social.getSocial_url()));

                    startActivity(intent);

                }
            });

        if (social != null){

            setContactName.setText(social.getSocial_name());
            setContactLink.setText(social.getSocial_url());

        }

        Button backButton = view.findViewById(R.id.go_back_button_social);
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

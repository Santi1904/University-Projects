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
import com.example.braguia.model.Objects.Partner;
import com.example.braguia.model.Objects.Social;

public class PartnerInfoFragment extends Fragment {

    private Partner partner;

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (getArguments() != null) {
            partner = (Partner) getArguments().getSerializable("selectedPartner");
        }
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_partner_info, container, false);

        TextView setPartnerName = view.findViewById(R.id.setPartnerName);
        TextView setPartnerPhone = view.findViewById(R.id.setPartnerPhone);
        TextView setPartnerLink = view.findViewById(R.id.setPartnerLink);
        TextView setPartnerEmail = view.findViewById(R.id.setPartnerEmail);

        ImageView link = view.findViewById(R.id.partnerLink);

        link.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {


                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse(partner.getPartner_url()));

                startActivity(intent);

            }
        });

        if (partner != null){

            setPartnerName.setText(partner.getPartner_name());
            setPartnerPhone.setText(partner.getPartner_phone());
            setPartnerLink.setText(partner.getPartner_url());
            setPartnerEmail.setText(partner.getPartner_mail());

        }

        Button backButton = view.findViewById(R.id.go_back_button_partner);
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

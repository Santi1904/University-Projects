package com.example.braguia.ui;

import android.content.Intent;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProvider;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;

import com.example.braguia.R;
import com.example.braguia.viewModel.UserViewModel;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link ProfileFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class ProfileFragment extends Fragment {

    // TODO: Rename parameter arguments, choose names that match
    // the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
    private static final String ARG_PARAM1 = "param1";
    private static final String ARG_PARAM2 = "param2";

    private UserViewModel userViewModel;

    private TextView usertype;
    private TextView username;

    private TextView dateSince;

    private TextView setLastLogin;

    private TextView setActive;

    private Button trailHist;

    private Button logout;

    private ImageButton settings;

    private Boolean is_active;

    private String date;

    private String lastLogin;

    private String formatted_date;

    private Date member_since;

    private Date last_login;

    private String formatted_last_login;


    // TODO: Rename and change types of parameters
    private String mParam1;
    private String mParam2;

    public ProfileFragment() {
        // Required empty public constructor
    }

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @param param1 Parameter 1.
     * @param param2 Parameter 2.
     * @return A new instance of fragment ProfileFragment.
     */
    // TODO: Rename and change types and number of parameters
    public static ProfileFragment newInstance(String param1, String param2) {
        ProfileFragment fragment = new ProfileFragment();
        Bundle args = new Bundle();
        args.putString(ARG_PARAM1, param1);
        args.putString(ARG_PARAM2, param2);
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (getArguments() != null) {
            mParam1 = getArguments().getString(ARG_PARAM1);
            mParam2 = getArguments().getString(ARG_PARAM2);
        }
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_profile, container, false);

        username     = view.findViewById(R.id.userName);
        usertype     = view.findViewById(R.id.userType);
        dateSince    = view.findViewById(R.id.setDate);
        setActive    = view.findViewById(R.id.setActive);
        setLastLogin = view.findViewById(R.id.setLastLogin);
        trailHist    = view.findViewById(R.id.traislHist);

        userViewModel = new ViewModelProvider(this).get(UserViewModel.class);
        userViewModel.getUser().observe(getViewLifecycleOwner(),user -> {
            username.setText(user.getUsername());
            usertype.setText(user.getUser_type());
            date = user.getDate_joined();
            lastLogin = user.getLast_login();

            SimpleDateFormat inputFormat = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss.SSSSSS'Z'");
            SimpleDateFormat outputFormat = new SimpleDateFormat("dd-MM-yyyy");
            SimpleDateFormat outputFormatLL = new SimpleDateFormat("dd-MM-yyyy HH:mm:ss");

            try {
                member_since = inputFormat.parse(date);
                last_login   = inputFormat.parse(lastLogin);
            } catch (ParseException e) {
                throw new RuntimeException(e);
            }
            formatted_date = outputFormat.format(member_since);
            formatted_last_login = outputFormatLL.format(last_login);


            dateSince.setText(formatted_date);
            setLastLogin.setText(formatted_last_login);

            is_active = user.isIs_active();

            if (is_active){
                setActive.setCompoundDrawablesWithIntrinsicBounds(R.drawable.circle_green, 0, 0, 0);
            }
            else{
                setActive.setCompoundDrawablesWithIntrinsicBounds(R.drawable.circle_red, 0, 0, 0);
            }


        });

        settings = view.findViewById(R.id.settingsButton);
        settings.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(getContext(),SettingsActivity.class));
            }
        });


        logout = view.findViewById(R.id.logoutButtonn);
        logout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                userViewModel.logout();

                userViewModel.getLogoutStatus().observe(getViewLifecycleOwner(), success -> {

                    if (success){
                        Toast.makeText(getContext(), "LOGOUT EFETUADO COM SUCESSO!", Toast.LENGTH_SHORT).show();
                        startActivity(new Intent(getContext(),AppLandingPage.class));
                    }
                    else {
                        Toast.makeText(getContext(), "ERRO NO LOGOUT", Toast.LENGTH_SHORT).show();
                    }
                } );
            }
        });

        trailHist.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                NavController navController = Navigation.findNavController(requireActivity(), R.id.nav_host_fragment);
                navController.navigate(R.id.action_ProfileFragment_to_TrailHistoryFragment);
            }
        });
        return view;
    }

    @Override
    public void onResume() {
        super.onResume();
        ((MainActivity) getActivity()).showBottomNavigationView();
    }
}
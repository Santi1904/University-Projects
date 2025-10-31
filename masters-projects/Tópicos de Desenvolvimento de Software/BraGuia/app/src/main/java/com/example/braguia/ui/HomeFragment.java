package com.example.braguia.ui;

import android.Manifest;
import android.app.KeyguardManager;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;
import androidx.lifecycle.ViewModelProvider;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import androidx.navigation.fragment.NavHostFragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.example.braguia.R;
import com.example.braguia.model.Objects.Edge;
import com.example.braguia.model.Objects.Trail;
import com.example.braguia.viewModel.LocationService;
import com.example.braguia.viewModel.TrailsViewModel;
import com.google.android.gms.maps.model.LatLng;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

public class HomeFragment extends Fragment {

    private TrailsViewModel trailsViewModel;

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        trailsViewModel = new ViewModelProvider(this).get(TrailsViewModel.class);
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_home, container, false);

        RecyclerView recyclerView = view.findViewById(R.id.trail_list);
        recyclerView.setLayoutManager(new LinearLayoutManager(getActivity(), LinearLayoutManager.HORIZONTAL, false));

        trailsViewModel.getAllTrails().observe(getViewLifecycleOwner(), trails -> {
            TrailsRecyclerViewAdapter adapter = new TrailsRecyclerViewAdapter(trails, new TrailsRecyclerViewAdapter.TrailClickListener() {

                @Override
                public void onItemClick(int position) {
                    Trail selectedTrail = trails.get(position);
                    Bundle bundle = new Bundle();
                    bundle.putSerializable("selectedTrail", selectedTrail);

                    NavController navController = Navigation.findNavController(requireActivity(), R.id.nav_host_fragment);
                    navController.navigate(R.id.action_HomeFragment_to_TrailFragment, bundle);

                }
            });
            recyclerView.setAdapter(adapter);
        });

        ImageView upgrade_to_premium = view.findViewById(R.id.upgrade_to_premium);
        upgrade_to_premium.setOnClickListener(v -> {
            NavController navController = Navigation.findNavController(v);
            navController.navigate(R.id.action_HomeFragment_to_UpgradeToPremium);
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
        ((MainActivity) getActivity()).showBottomNavigationView();
    }
}

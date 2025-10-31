package com.example.braguia.ui;


import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.os.Bundle;
import android.os.Parcelable;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.fragment.app.FragmentManager;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProvider;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.example.braguia.R;
import com.example.braguia.model.Objects.Edge;
import com.example.braguia.model.Objects.Pin;
import com.example.braguia.model.Objects.Trail;
import com.example.braguia.viewModel.TrailsViewModel;

import com.example.braguia.viewModel.UserViewModel;
import com.google.android.gms.location.FusedLocationProviderClient;
import com.google.android.gms.location.LocationServices;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.MapsInitializer;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.model.LatLng;
import com.squareup.picasso.Picasso;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.concurrent.atomic.AtomicBoolean;

public class TrailFragment extends Fragment implements OnMapReadyCallback {

    private Trail trail;
    private ArrayList<LatLng> coordinates;
    private GoogleMap googleMap;
    private FusedLocationProviderClient fusedLocationClient;
    private static final int MY_PERMISSIONS_REQUEST_LOCATION = 1001;
    private TrailsViewModel trailsViewModel;
    private UserViewModel userViewModel;

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        if (getArguments() != null) {
            trail = (Trail) getArguments().getSerializable("selectedTrail");
            trailsViewModel = new ViewModelProvider(this).get(TrailsViewModel.class);
            userViewModel = new ViewModelProvider(this).get(UserViewModel.class);
        }
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_trail, container, false);

        coordinates = new ArrayList<>();

        TextView trail_name = view.findViewById(R.id.trail_trail_name);
        trail_name.setText(trail.getTrail_name());

        TextView trail_desc = view.findViewById(R.id.trail_trail_desc);
        trail_desc.setText(trail.getTrail_desc());

        TextView trail_duration = view.findViewById(R.id.trail_trail_duration);
        trail_duration.setText(trail.getTrail_duration() + " min");

        fusedLocationClient = LocationServices.getFusedLocationProviderClient(getActivity());

        ImageView difficulty_image = view.findViewById(R.id.trail_trail_difficulty);
        switch (trail.getTrail_difficulty()) {
            case "E":
                difficulty_image.setImageResource(R.drawable.easy);
                break;

            case "M":
                difficulty_image.setImageResource(R.drawable.medium);
                break;

            case "H":
                difficulty_image.setImageResource(R.drawable.hard);
                break;

            default:
                difficulty_image.setImageResource(R.drawable.easy);
                break;
        }

        ImageView imageView = view.findViewById(R.id.trail_trail_image);
        Picasso.get()
                .load(trail.getTrail_img().replace("http:", "https:"))
                .into(imageView);

        ImageView backButton = view.findViewById(R.id.backButton);
        backButton.setOnClickListener(v -> {
            NavController navController = Navigation.findNavController(v);
            navController.navigate(R.id.action_TrailFragment_to_HomeFragment);

            });

/*
        ImageView favButton = view.findViewById(R.id.favButton);
        favButton.setOnClickListener(v -> {

            int[] normalState = {android.R.attr.state_enabled};
            int[] pressedState = {android.R.attr.state_pressed};

            Drawable currentDrawable = favButton.getDrawable();
            currentDrawable.setState(normalState);
            Drawable favoriteTrueDrawable = ContextCompat.getDrawable(getActivity(), R.drawable.favorite_true);


            if (Arrays.equals(currentDrawable.getState(), normalState)) {
                favButton.setImageResource(R.drawable.favorite_true);
                currentDrawable.setState(pressedState);
            } else {
                favButton.setImageResource(R.drawable.favorite_false);
                currentDrawable.setState(normalState);
            }
        });
*/

        RecyclerView recyclerView = view.findViewById(R.id.trail_pin_list);
        recyclerView.setLayoutManager(new LinearLayoutManager(getActivity(), LinearLayoutManager.HORIZONTAL, false));
        trailsViewModel.getPinsOfTrail(trail.getId()).observe(getViewLifecycleOwner(), pins -> {

            List<Pin> pinsList = new ArrayList<>();

            for (Pin pin : pins) {
                boolean nameExists = false;
                for (Pin existingPin : pinsList) {
                    if (pin.getPin_name().equals(existingPin.getPin_name())) {
                        nameExists = true;
                        break;
                    }
                }
                if (!nameExists) {
                    pinsList.add(pin);
                }
            }

            PinsRecyclerViewAdapter adapter = new PinsRecyclerViewAdapter(pinsList, new PinsRecyclerViewAdapter.PinClickListener() {
                @Override
                public void onItemClick(int position) {
                    Pin selectedPin = pins.get(position);
                    Bundle bundle = new Bundle();
                    bundle.putSerializable("selectedPin", selectedPin);
                    bundle.putSerializable("trackbackTrail", trail);
                    NavController navController = Navigation.findNavController(requireActivity(), R.id.nav_host_fragment);
                    navController.navigate(R.id.action_TrailFragment_to_PinFragment, bundle);
                }
            });
            recyclerView.setAdapter(adapter);
        });


        Button navButton = view.findViewById(R.id.navButton);
        userViewModel.getUser().observe(getViewLifecycleOwner(), user -> {
            if (!user.getUser_type().equals("Premium")) {
                navButton.setVisibility(View.GONE);
            }
        });
        navButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (ContextCompat.checkSelfPermission(requireContext(), Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
                    ActivityCompat.requestPermissions(requireActivity(), new String[]{Manifest.permission.ACCESS_FINE_LOCATION}, MY_PERMISSIONS_REQUEST_LOCATION);
                } else {
                    assert getArguments() != null;
                    Trail trail_hist = (Trail) getArguments().getSerializable("selectedTrail");
                    assert trail_hist != null;
                    trailsViewModel.insertTrailHistory(trail_hist);
                    setGoogleMap();
                }
            }
        });

        return view;
    }

    public void setGoogleMap() {
        trail = (Trail) getArguments().getSerializable("selectedTrail");

        for (Edge edge : trail.getEdges()){
            LatLng trailLocation_start = new LatLng(edge.getEdge_start().getPin_lat(), edge.getEdge_start().getPin_lng());
            LatLng trailLocation_end = new LatLng(edge.getEdge_end().getPin_lat(), edge.getEdge_end().getPin_lng());
            coordinates.add(trailLocation_start);
            coordinates.add(trailLocation_end);
        }
        if (coordinates.size() < 2){
            System.out.println("Coordenadas insuficientes");
        } else{
            // Remover repetidos
            Set<LatLng> noReps = new HashSet<>(coordinates);

            LatLng startingPoint = coordinates.get(0);
            LatLng endingPoint = coordinates.get(coordinates.size() - 1);
            List<LatLng> waypoints = new ArrayList<>(noReps);

            waypoints.remove(startingPoint);
            waypoints.remove(endingPoint);

            if (ContextCompat.checkSelfPermission(requireContext(), Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED) {
                fusedLocationClient.getLastLocation().addOnSuccessListener(getActivity(), location -> {
                    if (location != null) {
                        LatLng currentLocation = new LatLng(location.getLatitude(), location.getLongitude());
                        LatLng newStartingPoint = currentLocation;

                        StringBuilder uriBuilder = new StringBuilder("https://www.google.com/maps/dir/?api=1");

                        uriBuilder.append("&origin=").append(newStartingPoint.latitude).append(",").append(startingPoint.longitude);
                        uriBuilder.append("&destination=").append(endingPoint.latitude).append(",").append(endingPoint.longitude);

                        if (!waypoints.isEmpty()) {
                            uriBuilder.append("&waypoints=");
                            for (LatLng waypoint : waypoints) {
                                uriBuilder.append(waypoint.latitude).append(",").append(waypoint.longitude).append("|");
                            }
                            uriBuilder.deleteCharAt(uriBuilder.length() - 1); // Remover o último "|"
                        }
                        Uri gmmIntentUri = Uri.parse(uriBuilder.toString());

                        Intent mapIntent = new Intent(Intent.ACTION_VIEW, gmmIntentUri);
                        mapIntent.setPackage("com.google.android.apps.maps");

                        if (ContextCompat.checkSelfPermission(requireContext(), Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
                            ActivityCompat.requestPermissions(requireActivity(), new String[]{Manifest.permission.ACCESS_FINE_LOCATION}, MY_PERMISSIONS_REQUEST_LOCATION);
                        } else {
                            startActivity(mapIntent);
                        }
                    } else {
                        Log.e("TrailFragment", "Falha ao obter a localização do dispositivo");
                    }
                });
            } else {
                Log.e("TrailFragment", "Permissão ACCESS_FINE_LOCATION não dada");
            }
        }
    }

    @Override
    public void onPause() {
        super.onPause();
    }

    @Override
    public void onResume() {
        super.onResume();
        ((MainActivity) getActivity()).hideBottomNavigationView();
    }

    @Override
    public void onMapReady(@NonNull GoogleMap googleMap) {
        MapsInitializer.initialize(getContext());
        this.googleMap = googleMap;
    }

}



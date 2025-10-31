package com.example.braguia.ui;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.lifecycle.LiveData;
import androidx.lifecycle.ViewModelProvider;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.example.braguia.R;
import com.example.braguia.model.Objects.Trail;
import com.example.braguia.viewModel.TrailsViewModel;

import java.util.ArrayList;
import java.util.List;

public class TrailHistoryFragment extends Fragment {

    private LiveData<List<Trail>> trailsHist; // = new LiveData<List<Trail>>();

    private List<Trail> history = new ArrayList<>();

    private TrailsViewModel trailsViewModel;

    private TrailHistoryAdapter adapter;

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        trailsViewModel = new ViewModelProvider(this).get(TrailsViewModel.class);
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_trail_history, container, false);

        RecyclerView recyclerView = view.findViewById(R.id.history_view);
        ImageView delete_history = view.findViewById(R.id.delete_history);
        ImageView backButton = view.findViewById(R.id.backButton);
        recyclerView.setLayoutManager(new LinearLayoutManager(getActivity(), LinearLayoutManager.VERTICAL, false));
        adapter = new TrailHistoryAdapter(new ArrayList<>());

        recyclerView.setAdapter(adapter);

        trailsHist = trailsViewModel.getTrailHistory();

        if (trailsHist != null) {
            trailsHist.observe(getViewLifecycleOwner(), trails -> {
                if (trails != null) {
                    adapter.setTrails(trails);
                }
            });
        }
        delete_history.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                trailsViewModel.deleteHistory();
                adapter.clear();
            }
        });

        backButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                NavController navController = Navigation.findNavController(v);
                navController.navigate(R.id.action_TrailHistoryFragment_to_ProfileFragment);
            }
        });
        return view;
    }
}

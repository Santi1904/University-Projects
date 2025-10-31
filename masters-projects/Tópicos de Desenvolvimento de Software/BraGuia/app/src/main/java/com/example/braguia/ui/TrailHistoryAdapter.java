package com.example.braguia.ui;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import androidx.recyclerview.widget.RecyclerView;

import com.example.braguia.R;
import com.example.braguia.model.Objects.Trail;
import com.squareup.picasso.Picasso;

import java.util.ArrayList;
import java.util.List;

public class TrailHistoryAdapter extends RecyclerView.Adapter<TrailHistoryAdapter.ViewHolder> {

    private List<Trail> trails;

    public TrailHistoryAdapter (List<Trail> tr) {
        trails = tr;
    }

    private TrailClickListener trailClickListener;


    @NonNull
    @Override
    public TrailHistoryAdapter.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View v = LayoutInflater.from(parent.getContext()).inflate(R.layout.fragment_trail_card,parent,false);
        return new TrailHistoryAdapter.ViewHolder(v);
    }

    @Override
    public void onBindViewHolder(@NonNull TrailHistoryAdapter.ViewHolder holder, int position) {


        if (!trails.isEmpty()){
            Trail trail = trails.get(position);

            holder.mTrailName.setText(trail.getTrail_name());
            Picasso.get()
                    .load(trail.getTrail_img().replace("http:", "https:"))
                    .into(holder.mTrailImage);

            holder.itemView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {

                    Context context = holder.itemView.getContext();

                    Bundle bundle = new Bundle();
                    bundle.putSerializable("selectedTrail", trail);

                    NavController navController = Navigation.findNavController((Activity) context, R.id.nav_host_fragment);
                    navController.navigate(R.id.action_TrailHistoryFragment_to_TrailFragment, bundle);
                }
            });
        }
    }

    public void setTrails(List<Trail> newTrails) {

        this.trails = newTrails;
        notifyDataSetChanged();
    }

    @Override
    public int getItemCount() {
        return trails.size();
    }

    public void clear(){

        int size = trails.size();
        trails.clear();
        notifyItemRangeRemoved(0,size);

    }

    public static class ViewHolder extends RecyclerView.ViewHolder {
        private final TextView mTrailName;
        private final ImageView mTrailImage;

        public ViewHolder(View view) {
            super(view);
            mTrailName = view.findViewById(R.id.trail_name);
            mTrailImage = view.findViewById(R.id.trail_image);
        }

        @Override
        public String toString() {
            return super.toString() + mTrailName;
        }
    }

    public interface TrailClickListener {
        void onItemClick(int position);
    }


}

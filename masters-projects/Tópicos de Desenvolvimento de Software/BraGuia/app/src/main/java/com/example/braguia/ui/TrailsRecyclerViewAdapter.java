package com.example.braguia.ui;

import android.annotation.SuppressLint;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.recyclerview.widget.RecyclerView;
import android.widget.ImageView;
import android.widget.TextView;
import com.example.braguia.model.Objects.Trail;
import com.squareup.picasso.Picasso;
import com.example.braguia.R;

import java.util.List;

public class TrailsRecyclerViewAdapter extends RecyclerView.Adapter<TrailsRecyclerViewAdapter.ViewHolder> {

    private List<Trail> mTrails;

    private TrailClickListener trailClickListener;

    public TrailsRecyclerViewAdapter(List<Trail> trails, TrailClickListener clickListener) {
        mTrails = trails;
        trailClickListener = clickListener;
    }

    @Override
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.fragment_trail_card, parent, false);
        return new ViewHolder(view);
    }

    @Override
    public void onBindViewHolder(final ViewHolder holder, int position) {
        Trail trail = mTrails.get(position);

        holder.mTrailName.setText(trail.getTrail_name());
        Picasso.get()
                .load(trail.getTrail_img().replace("http:", "https:"))
                .into(holder.mTrailImage);

        holder.itemView.setOnClickListener(v -> {
            if (trailClickListener != null) {
                trailClickListener.onItemClick(position);
            }
        });
    }

    @Override
    public int getItemCount() {
        return mTrails.size();
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

    public Trail getTrail(int position) {
        return mTrails.get(position);
    }

    public void setTrails(List<Trail> trails) {
        mTrails = trails;
    }

    public interface TrailClickListener {
        void onItemClick(int position);
    }

    public void setTrailClickListener(TrailClickListener trailClickListener) {
        this.trailClickListener = trailClickListener;
    }
}

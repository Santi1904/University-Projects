package com.example.braguia.ui;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.recyclerview.widget.RecyclerView;

import android.widget.TextView;

import com.example.braguia.model.Objects.Social;
import com.example.braguia.R;

import java.util.List;

public class SocialRecyclerViewAdapter extends RecyclerView.Adapter<SocialRecyclerViewAdapter.ViewHolder> {

    private List<Social> socials;

    private SocialClickListener clickListener;

    public SocialRecyclerViewAdapter(List<Social> socials, SocialClickListener clickListener){

        this.socials = socials;
        this.clickListener = clickListener;
    }


    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType){
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.fragment_social_card, parent, false);
        return new ViewHolder(view);
    }


    public void onBindViewHolder(final SocialRecyclerViewAdapter.ViewHolder holder, int position) {
        Social social = socials.get(position);

        holder.contact_name_social.setText(social.getSocial_name());

        holder.itemView.setOnClickListener(v -> {
            if (clickListener != null) {
                clickListener.onItemClick(position);
            }
        });
    }

    @Override
    public int getItemCount() {
        return socials.size();
    }

    public interface SocialClickListener {
        void onItemClick(int position);
    }

    public static class ViewHolder extends RecyclerView.ViewHolder {
        private final TextView contact_name_social;

        public ViewHolder(View view) {
            super(view);
            contact_name_social = view.findViewById(R.id.contact_name_social);

        }

        @Override
        public String toString() {
            return super.toString() + contact_name_social;
        }
    }
}

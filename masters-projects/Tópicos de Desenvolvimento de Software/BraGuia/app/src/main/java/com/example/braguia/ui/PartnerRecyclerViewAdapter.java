package com.example.braguia.ui;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.recyclerview.widget.RecyclerView;

import android.widget.TextView;

import com.example.braguia.model.Objects.Partner;
import com.example.braguia.model.Objects.Social;
import com.example.braguia.R;

import java.util.List;

public class PartnerRecyclerViewAdapter extends RecyclerView.Adapter<PartnerRecyclerViewAdapter.ViewHolder> {

    private List<Partner> partners;

    private SocialClickListener clickListener;

    public PartnerRecyclerViewAdapter(List<Partner> partners, SocialClickListener clickListener){

        this.partners = partners;
        this.clickListener = clickListener;
    }


    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType){
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.fragment_partner_card, parent, false);
        return new ViewHolder(view);
    }


    public void onBindViewHolder(final PartnerRecyclerViewAdapter.ViewHolder holder, int position) {
        Partner partner = partners.get(position);

        holder.partner_name.setText(partner.getPartner_name());

        holder.itemView.setOnClickListener(v -> {
            if (clickListener != null) {
                clickListener.onItemClick(position);
            }
        });
    }

    @Override
    public int getItemCount() {
        return partners.size();
    }

    public interface SocialClickListener {
        void onItemClick(int position);
    }

    public static class ViewHolder extends RecyclerView.ViewHolder {
        private final TextView partner_name;

        public ViewHolder(View view) {
            super(view);
            partner_name = view.findViewById(R.id.partner_name);

        }

        @Override
        public String toString() {
            return super.toString() + partner_name;
        }
    }
}

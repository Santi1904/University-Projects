package com.example.braguia.ui;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;

import com.example.braguia.R;
import com.example.braguia.model.Objects.Pin;
import com.example.braguia.model.Objects.Trail;
import com.squareup.picasso.Picasso;

import java.util.List;
import java.util.Objects;

public class PinsRecyclerViewAdapter extends RecyclerView.Adapter<PinsRecyclerViewAdapter.ViewHolder> {

    private List<Pin> mPins;

    private PinClickListener pinClickListener;

    public PinsRecyclerViewAdapter(List<Pin> pins, PinClickListener clickListener) {
        mPins = pins;
        pinClickListener = clickListener;
    }

    @Override
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.fragment_pin_card, parent, false);
        return new ViewHolder(view);
    }

    @Override
    public void onBindViewHolder(final ViewHolder holder, int position) {
        Pin pin = mPins.get(position);

        holder.mPinName.setText(pin.getPin_name());

        holder.itemView.setOnClickListener(view -> {
            if (pinClickListener != null) {
                pinClickListener.onItemClick(position);
            }
        });
    }

    @Override
    public int getItemCount() {
        return mPins.size();
    }

    public static class ViewHolder extends RecyclerView.ViewHolder {
        private final TextView mPinName;

        public ViewHolder(View view) {
            super(view);
            mPinName = view.findViewById(R.id.pin_name);
        }

        @Override
        public String toString() {
            return super.toString() + mPinName;
        }
    }


    public interface PinClickListener {
        void onItemClick(int position);
    }

    public void setTrailClickListener(PinClickListener pinClickListener) {
        this.pinClickListener = pinClickListener;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Pin pin = (Pin) o;
        return Objects.equals(pin.getId(), pin.getId());
    }

}

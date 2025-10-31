package com.example.braguia.ui;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.recyclerview.widget.RecyclerView;

import android.widget.TextView;

import com.example.braguia.model.Objects.Contact;
import com.example.braguia.R;

import java.util.List;

public class ContactRecyclerViewAdapter extends RecyclerView.Adapter<ContactRecyclerViewAdapter.ViewHolder> {

    private List<Contact> contacts;

    private ContactClickListener clickListener;

    public ContactRecyclerViewAdapter(List<Contact> contacts, ContactClickListener clickListener){

        this.contacts = contacts;
        this.clickListener = clickListener;
    }


    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType){
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.fragment_contact_card, parent, false);
        return new ViewHolder(view);
    }

    public void onBindViewHolder(final ContactRecyclerViewAdapter.ViewHolder holder, int position) {
        Contact contact = contacts.get(position);

        holder.contact_name.setText(contact.getContact_name());

        holder.itemView.setOnClickListener(v -> {
            if (clickListener != null) {
                clickListener.onItemClick(position);
            }
        });
    }

    @Override
    public int getItemCount() {
        return contacts.size();
    }

    public interface ContactClickListener {
        void onItemClick(int position);
    }

    public static class ViewHolder extends RecyclerView.ViewHolder {
        private final TextView contact_name;

        public ViewHolder(View view) {
            super(view);
            contact_name = view.findViewById(R.id.contact_name);

        }

        @Override
        public String toString() {
            return super.toString() + contact_name;
        }
    }
}

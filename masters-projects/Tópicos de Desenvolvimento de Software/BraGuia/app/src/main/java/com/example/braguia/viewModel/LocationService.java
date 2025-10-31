package com.example.braguia.viewModel;

import android.Manifest;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Typeface;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.location.LocationRequest;
import android.os.Build;
import android.os.Bundle;
import android.os.IBinder;
import android.os.Looper;
import android.provider.ContactsContract;
import android.text.Spannable;
import android.text.SpannableString;
import android.text.style.StyleSpan;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.core.app.ActivityCompat;
import androidx.core.app.NotificationCompat;
import androidx.core.content.ContextCompat;
import androidx.lifecycle.Lifecycle;
import androidx.lifecycle.LifecycleOwner;
import androidx.lifecycle.LifecycleRegistry;
import androidx.lifecycle.LiveData;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProvider;
import androidx.lifecycle.ViewModelStoreOwner;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;

import com.example.braguia.R;
import com.example.braguia.model.Objects.Edge;
import com.example.braguia.model.Objects.Pin;
import com.example.braguia.model.Objects.Trail;
import com.example.braguia.ui.MainActivity;
import com.example.braguia.ui.PinFragment;
import com.google.android.gms.location.FusedLocationProviderClient;
import com.google.android.gms.location.LocationCallback;
import com.google.android.gms.location.LocationResult;
import com.google.android.gms.location.LocationServices;
import com.google.android.gms.maps.model.LatLng;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class LocationService extends Service {
    private static final int NOTIFICATION_ID = 123;
    private static final String CHANNEL_ID = "1";
    private LocationManager locationManager;
    private LocationListener locationListener;
    private ArrayList<LatLng> coordinates;
    private ArrayList<Pin> pins;


    @Override
    public void onCreate() {
        super.onCreate();

        locationManager = (LocationManager) getSystemService(Context.LOCATION_SERVICE);
        getCoordinates();
        locationListener = new MyLocationListener();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        startForeground(NOTIFICATION_ID, buildNotification());
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED && ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            stopSelf();
        }
        locationManager.requestLocationUpdates(LocationManager.NETWORK_PROVIDER, 60000, 0, locationListener);
        return START_STICKY;
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        stopForeground(true);
        if (locationManager != null) {
            locationManager.removeUpdates(locationListener);
        }
    }

    private Notification buildNotification() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            NotificationChannel channel = new NotificationChannel(CHANNEL_ID, "Channel1", NotificationManager.IMPORTANCE_DEFAULT);
            NotificationManager notificationManager = getSystemService(NotificationManager.class);
            notificationManager.createNotificationChannel(channel);
        }

        return new NotificationCompat.Builder(this, CHANNEL_ID)
                .setContentTitle("BraGuia")
                .setContentText("Estamos a usar a sua localização!")
                .setSmallIcon(R.mipmap.ic_launcher_round)
                .setOngoing(true)
                .setOnlyAlertOnce(true)
                .build();
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    private class MyLocationListener implements LocationListener {
        @Override
        public void onLocationChanged(@NonNull Location location) {
            Log.d("LocationService", "Latitude: " + location.getLatitude() + ", Longitude: " + location.getLongitude());
            System.out.println("Latitude: " + location.getLatitude() + ", Longitude: " + location.getLongitude());

            checkForNearPOI(location);
        }

    }

    public void checkForNearPOI(Location userLocation){
        float distanceThreshold = 4000; // metros

        LatLng userPosition = new LatLng(userLocation.getLatitude(), userLocation.getLongitude());
        if (coordinates != null){
            for (LatLng pinPosition : coordinates) {
                double distance = calculateDistance(userPosition, pinPosition);
                if (distance < distanceThreshold) {
                    for (Pin pin : pins){
                        if (pinPosition.latitude == pin.getPin_lat() && pinPosition.longitude == pin.getPin_lng()){
                            String name = pin.getPin_name();
                            sendNotification(this,  "Estás próximo de um ponto de interesse: " + name + ". Toca para saberes mais!", pin);
                        }
                    }
                }
            }
        }
    }

    private void sendNotification(Context context, String message, Pin pin) {
        NotificationManager notificationManager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
        if (notificationManager == null) {
            return;
        }

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            CharSequence channelName = "POI Notification Channel";
            int importance = NotificationManager.IMPORTANCE_DEFAULT;
            NotificationChannel channel = new NotificationChannel(CHANNEL_ID, channelName, importance);
            notificationManager.createNotificationChannel(channel);
        }

        SpannableString spannableMessage = new SpannableString(message);
        String poiName = pin.getPin_name();
        int startIndex = message.indexOf(poiName);
        int endIndex = startIndex + poiName.length();
        spannableMessage.setSpan(new StyleSpan(Typeface.BOLD), startIndex, endIndex, Spannable.SPAN_EXCLUSIVE_EXCLUSIVE);

        Intent intent = new Intent(context, MainActivity.class);
        intent.putExtra("selectedPin", pin);
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        PendingIntent pendingIntent = PendingIntent.getActivity(context, 0, intent, PendingIntent.FLAG_UPDATE_CURRENT | PendingIntent.FLAG_IMMUTABLE);

        NotificationCompat.Builder builder = new NotificationCompat.Builder(context, CHANNEL_ID)
                .setSmallIcon(R.mipmap.ic_launcher_round)
                .setContentTitle("Ponto de Interesse")
                .setContentText(spannableMessage)
                .setPriority(NotificationCompat.PRIORITY_DEFAULT)
                .setContentIntent(pendingIntent);

        Notification notification = builder.build();
        notificationManager.notify(0, notification);
    }


    private double calculateDistance(LatLng latLng1, LatLng latLng2) {
        double earthRadius = 6371000;

        double lat1 = Math.toRadians(latLng1.latitude);
        double lon1 = Math.toRadians(latLng1.longitude);
        double lat2 = Math.toRadians(latLng2.latitude);
        double lon2 = Math.toRadians(latLng2.longitude);

        double dLat = lat2 - lat1;
        double dLon = lon2 - lon1;

        double a = Math.sin(dLat / 2) * Math.sin(dLat / 2) +
                Math.cos(lat1) * Math.cos(lat2) *
                        Math.sin(dLon / 2) * Math.sin(dLon / 2);

        double c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));

        return earthRadius * c;
    }

    public void getCoordinates(){
        coordinates = new ArrayList<>();
        pins = new ArrayList<>();
        TrailsViewModel trailsViewModel = new ViewModelProvider.AndroidViewModelFactory(getApplication()).create(TrailsViewModel.class);
        trailsViewModel.getAllTrails().observeForever(new Observer<List<Trail>>() {
            @Override
            public void onChanged(List<Trail> trails) {
                for (Trail t : trails){
                    for (Edge edge : t.getEdges()) {
                        pins.add(edge.getEdge_start());
                        pins.add(edge.getEdge_end());
                        coordinates.add(new LatLng(edge.getEdge_start().getPin_lat(), edge.getEdge_start().getPin_lng()));
                        coordinates.add(new LatLng(edge.getEdge_end().getPin_lat(), edge.getEdge_end().getPin_lng()));
                    }
                }
                Set<LatLng> uniqueCoordinates = new HashSet<>(coordinates);
                coordinates.clear();
                coordinates.addAll(uniqueCoordinates);
            }
        });

    }
}

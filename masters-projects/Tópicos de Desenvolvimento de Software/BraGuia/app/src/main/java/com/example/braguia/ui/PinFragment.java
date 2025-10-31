package com.example.braguia.ui;

import android.Manifest;
import android.app.DownloadManager;
import android.content.Context;
import android.content.pm.PackageManager;
import android.media.AudioAttributes;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.MediaController;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.VideoView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.RequiresApi;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProvider;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;

import com.example.braguia.R;
import com.example.braguia.model.Objects.Media;
import com.example.braguia.model.Objects.Pin;
import com.example.braguia.model.Objects.Trail;
import com.example.braguia.viewModel.UserViewModel;
import com.squareup.picasso.Picasso;

import java.io.File;
import java.io.IOException;
import java.util.List;


public class PinFragment extends Fragment {

    private Pin pin;

    private VideoView videoView;

    private ImageButton play_audio;

    private MediaPlayer mediaPlayer;

    private UserViewModel userViewModel;

    private Trail trackbackTrail;

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        assert getArguments() != null;
        pin = (Pin) getArguments().getSerializable("selectedPin");
        trackbackTrail = (Trail) getArguments().getSerializable("trackbackTrail");
        userViewModel = new ViewModelProvider(this).get(UserViewModel.class);



    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_pin, container, false);

        ScrollView scrollView = view.findViewById(R.id.scroll_view);
        scrollView.post(new Runnable() {
            @Override
            public void run() {
                scrollView.scrollTo(0, 0);
            }
        });

        TextView setPinName      = view.findViewById(R.id.setPinName);
        TextView setPinDesc      = view.findViewById(R.id.setPinDesc);
        TextView setLat          = view.findViewById(R.id.setLat);
        TextView setLng          = view.findViewById(R.id.setLng);
        TextView setAlt          = view.findViewById(R.id.setAlt);
        ImageButton backButton   = view.findViewById(R.id.backButton);
        ImageView pinImage       = view.findViewById(R.id.pin_image);
        videoView                = view.findViewById(R.id.videoView);
        play_audio               = view.findViewById(R.id.audio_button);
        Button download_video    = view.findViewById(R.id.download_video);
        Button play_video        = view.findViewById(R.id.play_video);
        TextView audio           = view.findViewById(R.id.audio);
        ImageView download_image = view.findViewById(R.id.download_image);
        ImageView download_audio = view.findViewById(R.id.download_audio);
        TextView premium_users   = view.findViewById(R.id.premium_users);


        setPinName.setText(pin.getPin_name());
        setPinDesc.setText(pin.getPin_desc());
        String latitude = getString(R.string.latitude) +" " + pin.getPin_lat();
        setLat.setText(latitude);
        String longitude = getString(R.string.longitude) + " " + pin.getPin_lng();
        setLng.setText(longitude);
        String altitude = getString(R.string.altitude) + " " + pin.getPin_alt();
        setAlt.setText(altitude);

        backButton.setOnClickListener(v -> {
            if (trackbackTrail != null) {
                Bundle bundle = new Bundle();
                bundle.putSerializable("selectedTrail", trackbackTrail);
                NavController navController = Navigation.findNavController(v);
                navController.navigate(R.id.action_PinFragment_to_TrailFragment, bundle);
            } else {
                requireActivity().finish();
            }
        });

        List<Media> media = pin.getMedia();

        videoView.setVisibility(View.GONE);
        download_video.setVisibility(View.GONE);
        download_image.setVisibility(View.GONE);
        play_video.setVisibility(View.GONE);
        download_audio.setVisibility(View.GONE);
        audio.setText(R.string.audio_na);
        play_audio.setEnabled(false);

        userViewModel.getUser().observe(getViewLifecycleOwner(), user -> {

            if (user.getUser_type().equals("Premium")){

                premium_users.setVisibility(View.GONE);

                for (Media m : media){

                    if (m != null){
                        switch (m.getMedia_type()) {
                            case "I":
                                Picasso.get()
                                        .load(m.getMedia_file().replace("http:", "https:"))
                                        .into(pinImage);

                                download_image.setVisibility(View.VISIBLE);
                                download_image.setOnClickListener(new View.OnClickListener() {
                                    @RequiresApi(api = Build.VERSION_CODES.TIRAMISU)
                                    @Override
                                    public void onClick(View v) {

                                        String file = m.getMedia_file();
                                        String fileName = extractTitleFromUrl(file);
                                        Uri url = Uri.parse(file);

                                        if (storageAllowed()) {
                                            ActivityCompat.requestPermissions(requireActivity(), new String[]{
                                                    Manifest.permission.READ_EXTERNAL_STORAGE,
                                                    Manifest.permission.READ_MEDIA_IMAGES
                                            }, 1);
                                            showToast("Por favor, conceda a permissão e tente novamente");
                                        } else {

                                            String folderPathVideo = requireActivity().getExternalFilesDir(null) + File.separator + "Download" + File.separator; // + "Image" + File.separator;

                                            File folder = new File(folderPathVideo);
                                            if (!folder.exists()) {
                                                folder.mkdirs();
                                            }
                                        }

                                        downloadMedia(url, fileName);
                                    }
                                });
                                break;
                            case "V": {

                                play_video.setVisibility(View.VISIBLE);
                                videoView.setVisibility(View.VISIBLE);
                                download_video.setVisibility(View.VISIBLE);

                                String video = m.getMedia_file().replace("http", "https");
                                Uri uri = Uri.parse(video);
                                String filename = extractTitleFromUrl(video);

                                videoView.setVideoURI(uri);
                                MediaController mediaController = new MediaController(getContext());
                                //mediaController.setAnchorView(videoView);
                                videoView.setMediaController(mediaController);
                                play_video.setOnClickListener(new View.OnClickListener() {
                                    @Override
                                    public void onClick(View v) {
                                        if (!videoView.isPlaying()) {
                                            videoView.start();
                                        } else {
                                            videoView.pause();
                                        }
                                    }
                                });

                                download_video.setOnClickListener(new View.OnClickListener() {
                                    @RequiresApi(api = Build.VERSION_CODES.TIRAMISU)
                                    @Override
                                    public void onClick(View v) {

                                        if (storageAllowed()) {
                                            ActivityCompat.requestPermissions(requireActivity(), new String[]{
                                                    Manifest.permission.READ_EXTERNAL_STORAGE,
                                                    Manifest.permission.READ_MEDIA_VIDEO
                                            }, 1);
                                            showToast("Por favor, conceda a permissão e tente novamente");
                                        } else {

                                            String folderPathVideo = requireActivity().getExternalFilesDir(null) + File.separator + "Download" + File.separator; // + "Video" + File.separator;

                                            File folder = new File(folderPathVideo);
                                            if (!folder.exists()) {
                                                folder.mkdirs();
                                            }

                                            if (uri == null) {
                                                showToast("URL de download não encontrada!");
                                                return;
                                            }

                                            downloadMedia(uri, filename);

                                        }
                                    }
                                });

                                break;
                            }
                            case "R": {

                                String url = m.getMedia_file().replace("http", "https");
                                String filename = extractTitleFromUrl(url);

                                audio.setText(R.string.play);
                                download_audio.setVisibility(View.VISIBLE);
                                play_audio.setEnabled(true);

                                mediaPlayer = new MediaPlayer();

                                mediaPlayer.setAudioAttributes(
                                        new AudioAttributes.Builder()
                                                .setContentType(AudioAttributes.CONTENT_TYPE_MUSIC)
                                                .setUsage(AudioAttributes.USAGE_MEDIA)
                                                .build()
                                );
                                mediaPlayer.setOnPreparedListener(new MediaPlayer.OnPreparedListener() {
                                    @Override
                                    public void onPrepared(MediaPlayer mp) {

                                        play_audio.setOnClickListener(new View.OnClickListener() {
                                            @Override
                                            public void onClick(View v) {

                                                if (!mediaPlayer.isPlaying()) {
                                                    mediaPlayer.start();
                                                    play_audio.setImageResource(R.drawable.stop_audio);
                                                } else {
                                                    mediaPlayer.pause();
                                                    play_audio.setImageResource(R.drawable.audio_green2);
                                                }
                                            }
                                        });
                                    }
                                });

                                try {
                                    mediaPlayer.setDataSource(url);
                                    mediaPlayer.prepareAsync();
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }

                                download_audio.setOnClickListener(new View.OnClickListener() {
                                    @RequiresApi(api = Build.VERSION_CODES.TIRAMISU)
                                    @Override
                                    public void onClick(View v) {

                                        if (storageAllowed()) {
                                            ActivityCompat.requestPermissions(requireActivity(), new String[]{
                                                    Manifest.permission.READ_EXTERNAL_STORAGE,
                                                    Manifest.permission.READ_MEDIA_AUDIO
                                            }, 1);
                                            showToast("Por favor, conceda a permissão e tente novamente");
                                        } else {

                                            String folderPathVideo = requireActivity().getExternalFilesDir(null) + File.separator + "Download" + File.separator; //+ "Audio" + File.separator;

                                            File folder = new File(folderPathVideo);
                                            if (!folder.exists()) {
                                                folder.mkdirs();
                                            }
                                            Uri audio_uri = Uri.parse(url);
                                            downloadMedia(audio_uri, filename);
                                        }
                                    }
                                });
                                break;
                            }
                        }
                    }
                }
            }
            else{
                premium_users.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        NavController navController = Navigation.findNavController(v);
                        navController.navigate(R.id.action_PinFragment_to_UpgradeFragment);
                    }
                });
            }
        });

        return view;
    }
    @RequiresApi(api = Build.VERSION_CODES.TIRAMISU)
    private boolean storageAllowed() {
        return ContextCompat.checkSelfPermission(requireContext(), Manifest.permission.READ_MEDIA_VIDEO) != PackageManager.PERMISSION_GRANTED;
    }

    private void showToast(String message) {
        Toast.makeText(requireContext(), message, Toast.LENGTH_SHORT).show();
    }

    private String extractTitleFromUrl(String url){
        int lastSlashIndex = url.lastIndexOf('/');

        return url.substring(lastSlashIndex + 1);
        
    }

    public void downloadMedia(Uri url, String fileName){

        if (url == null) {
            showToast("URL de download inválida!");
            return;
        }

        DownloadManager.Request req = new DownloadManager.Request(url);
        req.setTitle(fileName);
        req.setNotificationVisibility(DownloadManager.Request.VISIBILITY_VISIBLE_NOTIFY_COMPLETED);
        req.setDestinationInExternalFilesDir(requireActivity(),Environment.DIRECTORY_DOWNLOADS,fileName);

        DownloadManager dm = (DownloadManager) requireContext().getSystemService(Context.DOWNLOAD_SERVICE);
        dm.enqueue(req);

    }

    @Override
    public void onResume() {
        super.onResume();
        ((MainActivity) getActivity()).hideBottomNavigationView();
    }


}

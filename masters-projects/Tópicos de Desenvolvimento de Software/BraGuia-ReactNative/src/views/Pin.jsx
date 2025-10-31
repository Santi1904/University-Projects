// Dependencies
import { StyleSheet,Dimensions, View,Alert ,Text, Image, ScrollView,TouchableOpacity, Platform ,ImageBackground, PermissionsAndroid } from 'react-native';
import { useState, useEffect } from 'react';
import { useSelector } from 'react-redux';
// Styles and Components
import { Colors } from '../styles';
import BackButton from '../components/backButton';
import Button from '../components/Button';

import noImage from '../../assets/no_image.jpg';
import appBackground from '../../assets/app_background.jpeg';

import Icon from 'react-native-vector-icons/Entypo';
import Icon2 from 'react-native-vector-icons/AntDesign';
import Video from 'react-native-video';
import Sound from 'react-native-sound';
import React from 'react';
import RNFS from 'react-native-fs';
import NetInfo from '@react-native-community/netinfo';

const { width } = Dimensions.get('window');

import { selectUserInfo } from '../redux/selectors/selectors';
import { set } from 'date-fns';
import { se } from 'date-fns/locale';


export default function Pin({ route }) {
  const { pin } = route.params;
  const [isPlaying, setIsPlaying] = useState(false);
  const [hasAudio, setHasAudio] = useState(false);
  //const [videoPlaying, setVideoPlaying] = useState(false);
  const [isConnected, setIsConnected] = useState(true);
  const [localImagePath, setLocalImagePath] = useState(null);
  const [localVideoPath, setLocalVideoPath] = useState(null);
  const [localAudioPath, setLocalAudioPath] = useState(null);
  const soundRef = React.useRef(null);
  const userInfo = useSelector(selectUserInfo);
  const user_type = userInfo.user_type;

  useEffect(() => {
    const checkConnectivity = async () => {
      const state = await NetInfo.fetch();
      setIsConnected(state.isConnected);
    };

    checkConnectivity();
  }, []);

  useEffect(() => {
    
    const loadImage = async () => {

      let image = null;
      let video = null;
      let audio = null;

      for (let i = 0; i < pin.media.length; i++) {
        if (pin.media[i].media_type === 'I') {
          image = pin.media[i].media_file;
          const filename = image.split('/').pop();
          const localPath = `${RNFS.DownloadDirectoryPath}/${filename}`;
          const fileExists = await RNFS.exists(localPath);
          if (!isConnected && fileExists) {
            setLocalImagePath(`file://${localPath}`);
          } else if (isConnected) {
            setLocalImagePath(image);
          }
        }

        else if (pin.media[i].media_type === 'V') {
          video = pin.media[i].media_file;
          setLocalVideoPath(video);
          //const filename = video.split('/').pop();
          //const localPath = `${RNFS.DownloadDirectoryPath}/${filename}`;
          //console.log('localPath',localPath)
          //const fileExists = await RNFS.exists(localPath);
          //if (isConnected && fileExists) {
          //  setLocalVideoPath(`file://${localPath}`);
          //} else if (isConnected) {
          //  setLocalVideoPath(video);
          //}
          
        }
        else if (pin.media[i].media_type === 'R') {
          audio = pin.media[i].media_file;
          setLocalAudioPath(audio);
          //const filename = audio.split('/').pop();
          //const localPath = `${RNFS.DownloadDirectoryPath}/${filename}`;
          //const fileExists = await RNFS.exists(localPath);
          //console.log('file exists',fileExists)
          //if (isConnected && fileExists) {
          //  setLocalAudioPath(`file://${localPath}`);
          //} else if (isConnected) {
          //  setLocalAudioPath(audio);
          //}
      }
    };
  }

    loadImage();
  }, []);


  const playAudio = () => {
    if (soundRef.current) {
      if (isPlaying) {
        soundRef.current.pause();
      } else {
        soundRef.current.play();
      }
      setIsPlaying(!isPlaying);
    }
  };

  if (localAudioPath !== null && soundRef.current === null) {
    soundRef.current = new Sound(localAudioPath,null, (error) => {
      if (error) {
        console.log('Failed to load sound', error);
        setHasAudio(false);
      }
      else {
        setHasAudio(true);
      }
    });
  }

  const handleDownloadFile = async (file) => {
    try {
      let granted;
      let download;

      if (Platform.OS === 'android') {
        
        if (file === 'video') {
          granted = await PermissionsAndroid.request(
            PermissionsAndroid.PERMISSIONS.READ_MEDIA_VIDEO,
          );
          download = localVideoPath;
        } 
        else if (file === 'audio') {
          granted = await PermissionsAndroid.request(
            PermissionsAndroid.PERMISSIONS.READ_MEDIA_AUDIO,
          );
          download = localAudioPath;
        }
        else if (file === 'image') {
          granted = await PermissionsAndroid.request(
            PermissionsAndroid.PERMISSIONS.READ_MEDIA_IMAGES,
          );
          download = localImagePath;
        }

        if (granted === PermissionsAndroid.RESULTS.GRANTED) {
          downloadFile(download);
        }
      }
    }
    catch (error) {
      console.log(error);
  }
}


const downloadFile = async (file) => {
    
    const filename = file.split('/').pop();
    const dest = `${RNFS.DownloadDirectoryPath}/${filename}`;

    const download = RNFS.downloadFile({
      fromUrl: file,
      toFile: dest,
    });

    const result = await download.promise;
    if (result.statusCode === 200) {
      if (Platform.OS === 'android') {
        RNFS.scanFile(dest);
      }
      Alert.alert('Download completo', 'O ficheiro foi salvo na galeria.');
    } else {
      Alert.alert('Erro no download', 'Falha ao baixar o ficheiro.');
    }
  };


  return (
    <ImageBackground source={appBackground} style={styles.background}>
    <ScrollView style={styles.scrollView} contentContainerStyle={styles.scrollViewContent}>
      <View style={styles.mainContainer}>
        <View style={styles.backButtonContainer}>
          <BackButton />
        </View>
        <Text style={styles.pin_name}>{pin.pin_name}</Text>
        {localImagePath && (user_type === 'Premium') ? (
        <View style={styles.dowloadImageContainer}>  
          <Image 
            source={{ uri: localImagePath }} 
            style={styles.image} 
          />
          <TouchableOpacity onPress={() => handleDownloadFile('image')}>
          <Icon2 
            name='download' 
            size={25} 
            color={Colors.primaryColor} 
            style={styles.downloadImage} 
          />
          </TouchableOpacity>
        </View>
        ) : (
          <Image 
            source={noImage} 
            style={styles.image} 
          />
        )}

        <Text style={styles.coordTitle}>{'COORDENADAS: '}</Text>
        <View style={styles.coordsContainer}>
          <View style={styles.coordCard}>
            <View style={styles.coordItem}>
              <Icon 
                name="location-pin" 
                size={24} color="red" 
              />
              <Text style={styles.lat}>{`LATITUDE: ${pin.pin_lat}`}</Text>
            </View>
            <View style={styles.coordItem}>
              <Icon 
                name="location-pin" 
                size={24} 
                color="red" 
              />
              <Text style={styles.lat}>{`LONGITUDE: ${pin.pin_lng}`}</Text>
            </View>
            <View style={styles.coordItem}>
              <Icon 
                name="location-pin" 
                size={24} 
                color="red" 
              />
              <Text style={styles.lat}>{`ALTITUDE: ${pin.pin_alt}`}</Text>
            </View>
          </View>
        </View>
        <Text style={styles.desc}>{'DESCRIÇÃO: '}</Text>
        <View style={styles.coordCard}>
          <Text style={styles.pin_desc}>{pin.pin_desc}</Text>
        </View>
        <View style={styles.separator} />
        <View>
          <Text style={styles.videoTitle}>{'VÍDEO'}</Text>
          {user_type === 'Premium' && localVideoPath ? (
          <Icon2 
            name='checkcircle' 
            size={20} 
            color='green' 
            style={styles.check} 
          />
          ) : (
          <Icon 
            name='circle-with-cross' 
            size={20} 
            color='red' 
            style={styles.check} 
          />
          )}
        </View>
        {localVideoPath && (user_type === 'Premium') ? (
          <Video
            source={{ uri: localVideoPath }}
            style={{ width: width - 32, height: 300 }}
            paused={true}
            controls={true}
            resizeMode="contain"
            />
          ) : (
          <Text style={styles.noVideo}>{'Nenhum vídeo disponível'}</Text>
          )}
        {localVideoPath && (user_type === 'Premium') && (
        <View style={styles.downloadButtonContainer}>
          <TouchableOpacity 
            style={styles.downloadButton} 
            onPress={() => handleDownloadFile('video')}
          >
            <Text style={styles.downloadButtonText}>DOWNLOAD</Text>
            <Icon2 
              name='download' 
              size={20} 
              color={Colors.white} 
              style={styles.downloadIcon} 
            />
          </TouchableOpacity>
        </View>
        )}
        <View style={styles.separator} />
        <View>
          <Text style={styles.audioTitle}>{'ÁUDIO'}</Text>
          {user_type === 'Premium' && hasAudio ? (
          <Icon2 
            name='checkcircle' 
            size={20} 
            color='green' 
            style={styles.checkAudio} 
          />
          ) : (
          <Icon 
            name='circle-with-cross' 
            size={20} 
            color='red' 
            style={styles.checkAudio} 
          />
          )}
        </View>
        {hasAudio && (user_type === 'Premium') ? (
        <TouchableOpacity onPress={playAudio} style={styles.button}>
          <Icon2 
            name={isPlaying ? 'pause' : 'sound'} 
            size={30} 
            color={Colors.primaryColor} 
          />
        </TouchableOpacity>
      ) : (
        <Text style={styles.noAudio}>{'Nenhum áudio disponível'}</Text>
      )} 
      </View>
      {hasAudio && (user_type === 'Premium') && (
        <View style={styles.downloadButtonContainer}>
          <TouchableOpacity 
            style={styles.downloadButton}
            onPress={() => handleDownloadFile('audio')}
            >
            <Text style={styles.downloadButtonText}>DOWNLOAD</Text>
            <Icon2 name='download' size={20} color={Colors.white} style={styles.downloadIcon} />
          </TouchableOpacity>
        </View>
      )}
      <View style={styles.separator} />
    </ScrollView>
    </ImageBackground>
  );
}

const styles = StyleSheet.create({
  scrollView: {
    flex: 1,
  },
  scrollViewContent: {
    flexGrow: 1,
    justifyContent: 'center',
    alignItems: 'center',
    padding: 16,
  },
  background: {
    flex: 1,
    width: '100%',
    height: '100%',
    justifyContent: 'center',
    alignItems: 'center',
  },
  mainContainer: {
    flex: 1,
    justifyContent: 'flex-start',
    alignItems: 'center',
    width: '100%',
  },
  backButtonContainer: {
    alignSelf: 'flex-start',
    marginBottom: 20,
    marginTop: 80,
    marginBottom: -50,
  },
  dowloadImageContainer: {
    flexDirection: 'row',
    marginLeft: 30,
  },
  downloadImage: {
    marginLeft: 10,
    marginTop: 120,
  },
  pin_name: {
    fontSize: 24,
    color: Colors.black,
    fontWeight: 'bold',
    marginBottom: 10,
  },
  image: {
    width: 200,
    height: 250,
    marginVertical: 10,
    resizeMode: 'contain',
  },
  coordCard: {
    backgroundColor: `${Colors.primaryColor}50`,
    borderRadius: 20,
    padding: 10,
    marginBottom: 10,
    width: '100%',
    alignItems: 'flex-start',
    justifyContent: 'center',
  },
  coordTitle: {
    fontSize: 20,
    color: Colors.black,
    fontWeight: 'bold',
    marginBottom: 10,
    textAlign: 'center',
  },
  coordsContainer: {
    width: '100%',
    alignItems: 'flex-start',
  },
  coordItem: {
    flexDirection: 'row',
    alignItems: 'center',
    marginBottom: 10,
  },
  lat: {
    fontSize: 16,
    color: Colors.black,
    fontWeight: 'bold',
    marginLeft: 5,
  },
  desc: {
    fontSize: 20,
    color: Colors.black,
    fontWeight: 'bold',
    marginTop: 20,
  },
  pin_desc: {
    fontSize: 16,
    color: Colors.black,
    marginTop: 10,
  },
  mediaTitle: {
    fontSize: 20,
    color: Colors.black,
    fontWeight: 'bold',
    marginTop: 20,
    alignSelf: 'center',
  },
  separator: {
    borderBottomWidth: 1,
    borderBottomColor: Colors.primaryColor,
    width: '100%',
    marginTop: 30,
  },
  videoTitle: {
    fontSize: 20,
    color: Colors.black,
    fontWeight: 'bold',
    marginTop: 40,
    alignSelf: 'center',
    marginBottom: -30, 
  },
  check: {
    marginLeft: 90,
    marginTop: 7,
  },
  noVideo: {
    fontSize: 16,
    color: Colors.black,
    marginTop: 40,
  },
  downloadButtonContainer: {
    marginTop: 20,
    flexDirection: 'row',
    alignItems: 'center',
  },
  downloadButton: {
    flexDirection: 'row',
    alignItems: 'center',
    backgroundColor: Colors.primaryColor,
    padding: 10,
    borderRadius: 8,
    marginTop: 15,
  },
  downloadButtonText: {
    color: Colors.white,
    fontSize: 16,
    fontWeight: 'bold',
    marginRight: 8,
  },
  downloadIcon: {
    marginLeft: 5,
  },
  audioTitle: {
    fontSize: 20,
    color: Colors.black,
    fontWeight: 'bold',
    marginTop: 30,
    marginBottom: 20,
    alignSelf: 'center',
  },
  checkAudio: {
    marginLeft: 100,
    marginTop: -43,
    marginBottom: 40,
  },
  noAudio: {
    fontSize: 16,
    color: Colors.black,
    marginTop: -10,
  },
});

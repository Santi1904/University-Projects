// Dependencies
import { StyleSheet, View, Text, Image, ScrollView, ImageBackground, TouchableOpacity, Alert, Linking } from 'react-native';
import { useEffect, useState } from 'react';
import Icon from 'react-native-vector-icons/Ionicons';
import GetLocation from 'react-native-get-location';
import { getAsyncStoreData, setAsyncStoreData } from '../utils/async-storage';

// Styles and Components
import { Colors } from '../styles';
import BackButton from '../components/backButton';
import FavButton from '../components/favButton';
import Button from '../components/Button';
import appBackground from '../../assets/app_background.jpeg';

// Redux
import { useSelector } from 'react-redux';
import { selectUserType } from '../redux/selectors/selectors';


export default function Trail({ route, navigation }) {
  const { trail } = route.params;
  const [pins, setPins] = useState([]);
  const [currentTrailHistory, setCurrentTrailHistory] = useState([]);
  const userType = useSelector(selectUserType);

  useEffect(() => {
    const pinsMap = new Map();

    trail.edges.forEach((edge) => {
      if (!pinsMap.has(edge.edge_start.id)) {
        pinsMap.set(edge.edge_start.id, edge.edge_start);
      }
      if (!pinsMap.has(edge.edge_end.id)) {
        pinsMap.set(edge.edge_end.id, edge.edge_end);
      }
    });

    setPins(Array.from(pinsMap.values()));
  }, [trail.edges]);

  useEffect(() => {
    const fetchTrailHistory = async () => {
      try {
        const res = await getAsyncStoreData('trailHistory');
        if (res) {
          setCurrentTrailHistory(JSON.parse(res));
        }
      } catch (e) {
        console.log('Error fetching trail history:', e);
      }
    };

    fetchTrailHistory();
  }, []);

  const handleSelectPin = (pin) => {
    navigation.navigate('Pin', { pin });
  };

  const handleStartTrail = () => {
    if (userType == 'Premium') {
      let newTrailList = [];

      if (currentTrailHistory && currentTrailHistory.length > 0) {
        const trailIndex = currentTrailHistory.indexOf(trail.trail_name);

        if (trailIndex !== -1) { // trail already in history
          // removing trail from history
          newTrailList = [
            ...currentTrailHistory.slice(0, trailIndex),
            ...currentTrailHistory.slice(trailIndex + 1)
          ];
        } else {
          newTrailList = [...currentTrailHistory];
        }
      }

      newTrailList.unshift(trail.trail_name);
      setCurrentTrailHistory(newTrailList);

      const jsonValue = JSON.stringify(newTrailList);
      setAsyncStoreData('trailHistory', jsonValue);

      const coordinates = [];
      trail.edges.forEach(edge => {
        coordinates.push({ lat: edge.edge_start.pin_lat, lng: edge.edge_start.pin_lng });
        coordinates.push({ lat: edge.edge_end.pin_lat, lng: edge.edge_end.pin_lng });
      });

      const uniqueCoordinates = Array.from(new Set(coordinates.map(JSON.stringify))).map(JSON.parse);

      GetLocation.getCurrentPosition({
        enableHighAccuracy: true,
        timeout: 60000,
      })
        .then(location => {
          const { latitude, longitude } = location;
          const origin = `${latitude},${longitude}`;

          const firstPoint = `${uniqueCoordinates[0].lat},${uniqueCoordinates[0].lng}`;
          const waypoints = uniqueCoordinates.slice(1, -1).map(coord => `${coord.lat},${coord.lng}`).join('|');
          const destination = `${uniqueCoordinates[uniqueCoordinates.length - 1].lat},${uniqueCoordinates[uniqueCoordinates.length - 1].lng}`;

          let url = `https://www.google.com/maps/dir/?api=1&origin=${origin}&destination=${destination}`;
          if (waypoints) {
            url += `&waypoints=${firstPoint}|${waypoints}`;
          } else {
            url += `&waypoints=${firstPoint}`;
          }

          Linking.openURL(url);
        })
        .catch(error => {
          console.error(error);
        });
    } else {
      Alert.alert('Acesso Negado', 'Esta funcionalidade é exclusiva para utilizadores Premium.');
    }
  };

  return (
    <ImageBackground source={appBackground} style={styles.background}>
    <ScrollView>
      <BackButton />
      <FavButton />
      <Image source={{ uri: trail.trail_img }} style={styles.image} />
      <View style={styles.infoContainer}>
        <Text style={styles.title}>{trail.trail_name}</Text>
        <View style={styles.underTitle}>
          <View style={styles.durationContainer}>
            <Icon name="stopwatch-outline" size={24} color="black" />
            <Text style={styles.durationText}>{trail.trail_duration} min</Text>
          </View>
          {
            trail.trail_difficulty === 'E' ?
              <Image source={require('../../assets/easy.png')} style={{ width: 80, height: 35 }} /> :
              trail.trail_difficulty === 'M' ?
                <Image source={require('../../assets/medium.png')} style={{ width: 95, height: 45 }} /> :
                <Image source={require('../../assets/hard.png')} style={{ width: 80, height: 30 }} />
          }
        </View>
        <Text style={styles.descTitle}>Descrição:</Text>
        <Text style={styles.description}>{trail.trail_desc}</Text>
        <Text style={styles.pinsTitle}>Pontos de interesse:</Text>
        <View style={styles.pinsContainer}>
          {
            pins.map((pin, index) => (
              <TouchableOpacity key={index} style={styles.pin} onPress={() => handleSelectPin(pin)}>
                <Text style={{ color: "white" }}>{pin.pin_name}</Text>
                <Icon name="eye" size={18} color="white" style={{ marginLeft: 5 }} />
              </TouchableOpacity>
            ))
          }
        </View>
      </View>
      <View style={styles.startButton}>
        <Button title="INICIAR" onPress={() => handleStartTrail()} />
      </View>
    </ScrollView>
  </ImageBackground>  
  );
}

const styles = StyleSheet.create({
  image: {
    width: '50%',
    height: 250,
    marginTop: 30,
    alignSelf: 'center',
  },
  background: {
    flex: 1,
    width: '100%',
    height: '100%',
    justifyContent: 'center',
    alignItems: 'center',
    resizeMode: 'cover',
  },
  infoContainer: {
    padding: 18,
  },
  title: {
    fontSize: 24,
    fontWeight: 'bold',
    color: Colors.black,
    marginTop: 20,
  },
  underTitle: {
    flexDirection: 'row',
    justifyContent: 'space-between',
    alignItems: 'center',
    marginTop: 14,
  },
  durationContainer: {
    flexDirection: 'row',
    alignItems: 'center',
  },
  durationText: {
    fontSize: 16,
    color: Colors.black,
    marginLeft: 5,
  },
  descTitle: {
    fontSize: 18,
    fontWeight: 'bold',
    color: Colors.black,
    marginTop: 30,
  },
  description: {
    fontSize: 16,
    color: Colors.black,
    marginTop: 10,
    letterSpacing: 0.2,
  },
  pinsTitle: {
    fontSize: 18,
    fontWeight: 'bold',
    color: Colors.black,
    marginTop: 30,
  },
  pinsContainer: {
    flex: 5,
    flexDirection: 'row',
    flexWrap: 'wrap',
    marginTop: 10,
  },
  pin: {
    flexDirection: 'row',
    justifyContent: 'center',
    alignItems: 'center',
    height: 40,
    backgroundColor: Colors.primaryColor,
    padding: 10,
    borderRadius: 16,
    margin: 5,
  },
  startButton: {
    marginVertical: 30,
    marginHorizontal: 16,
  }
});

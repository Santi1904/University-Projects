// Dependencies
import { StyleSheet, TextInput, TouchableOpacity, View, Text, FlatList, ImageBackground } from 'react-native';
import { useEffect, useState } from 'react';
import LinearGradient from 'react-native-linear-gradient';
import Icon from 'react-native-vector-icons/Ionicons';
import { useIsFocused } from '@react-navigation/native';
import { getAsyncStoreData, setAsyncStoreData } from '../utils/async-storage';

// Redux
import { useDispatch, useSelector } from 'react-redux';
import { fetchTrails } from '../redux/actions/trailsActions';
import { selectTrailsStatus, selectTrails } from '../redux/selectors/selectors';

// Styles and Components
import { Colors } from '../styles';
import TrailCard from '../components/TrailCard';
import appBackground from '../../assets/app_background.jpeg';


export default function Home({ navigation }) {
  const dispatch = useDispatch();
  const isFocused = useIsFocused();
  const status = useSelector(selectTrailsStatus);
  const [searchInput, setSearchInput] = useState('');
  const trails = useSelector(selectTrails);
  const [userTrailHistory, setUserTrailHistory] = useState([]);
  const [isTrailsLoaded, setIsTrailsLoaded] = useState(false);

  useEffect(() => {
    dispatch(fetchTrails()).then(() => setIsTrailsLoaded(true));
  }, [dispatch]);

  useEffect(() => {
    if (isFocused && isTrailsLoaded) {
      getAsyncStoreData('trailHistory').then((res) => {
        if (res) {
          setUserTrailHistory(JSON.parse(res));
        }
      });
    }
  }, [isFocused, isTrailsLoaded]);


  const handleSearch = (text) => {
    if (text === '') {
      setSearchInput('');
    } else {
      const filteredTrails = trails.filter((trail) =>
        trail.trail_name.includes(text),
      );
      setSearchInput(filteredTrails);
    }
  };

  const handleOpenUpgrade = () => {
    navigation.navigate('Premium');
  };

  const renderItem = ({ item }) => (
    <TrailCard trail={item} navigation={navigation} />
  );

  const renderHistoryItem = ({ item }) => {
    const trail = trails.find((t) => t.trail_name === item);
    return <TrailCard trail={trail} navigation={navigation} />;
  };

  const handleCleanHistory = () => {
    // dispatch(deleteTrailHistory());
    setAsyncStoreData('trailHistory', JSON.stringify([]));
    setUserTrailHistory([]);
  };

  return (
    <>
      <LinearGradient
        colors={[Colors.primaryColor, Colors.secondaryColor]}
        style={styles.topContainer}>
        <View style={styles.searchBar}>
          <Icon
            name="search"
            size={24}
            color="black"
            style={styles.searchIcon}
          />
          <TextInput placeholder="Procurar..." onChangeText={handleSearch} />
        </View>
        <TouchableOpacity
          style={styles.premiumButton}
          onPress={() => handleOpenUpgrade()}>
          <Icon name="diamond" size={35} color="black" />
        </TouchableOpacity>
      </LinearGradient>
      <View>
        <View style={styles.trailsHeader}>
          <Text style={styles.trailsTitle}>Roteiros</Text>
          <Text style={styles.trailsSubtitle}>Ver todos</Text>
        </View>
        <FlatList
          data={trails}
          renderItem={renderItem}
          keyExtractor={(item) => item.id.toString()}
          horizontal
          showsHorizontalScrollIndicator={false}
          contentContainerStyle={styles.trailsContainer}
        />
      </View>
      {
        userTrailHistory && userTrailHistory.length > 0 &&
        <View style={{marginTop: 24}}>
          <View style={styles.trailsHeader}>
            <Text style={styles.trailsTitle}>Histórico de Roteiros</Text>
            <TouchableOpacity onPress={() => handleCleanHistory()}>
              <Icon name="trash" size={24} color="black" />
            </TouchableOpacity>
          </View>
          <FlatList
            data={userTrailHistory}
            renderItem={renderHistoryItem}
            keyExtractor={(item) => item}
            horizontal
            showsHorizontalScrollIndicator={false}
            contentContainerStyle={styles.trailsContainer}
          />
        </View>
      }
    </>
  );
}

const styles = StyleSheet.create({
  topContainer: {
    flexDirection: 'row',
    borderBottomRightRadius: 30,
    borderBottomLeftRadius: 30,
  },
  searchBar: {
    flex: 1,
    flexDirection: 'row',
    height: 60,
    backgroundColor: Colors.white,
    marginVertical: 20,
    marginLeft: 16,
    padding: 12,
    borderRadius: 10,
  },
  searchIcon: {
    marginRight: 5,
    marginTop: 4,
  },
  premiumButton: {
    marginTop: 16,
    padding: 16,
  },
  trailsHeader: {
    flexDirection: 'row',
    justifyContent: 'space-between',
    alignItems: 'center',
    marginHorizontal: 16,
    marginTop: 20,
  },
  trailsTitle: {
    fontSize: 24,
    fontWeight: 'bold',
    color: Colors.black,
  },
  trailsSubtitle: {
    fontSize: 12,
    fontWeight: 'bold',
    color: Colors.primaryColor,
    paddingTop: 12,
  },
  trailsContainer: {
    flexDirection: 'row',
    flexWrap: 'wrap',
    justifyContent: 'space-between',
    marginHorizontal: 16,
    marginTop: 10,
  },
});

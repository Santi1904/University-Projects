// Dependencies
import { StyleSheet, SafeAreaView, View, Text, ImageBackground, Image } from 'react-native';
import { useEffect, useState } from 'react';
import { getAsyncStoreData } from '../utils/async-storage';

// Redux
import { useDispatch, useSelector } from 'react-redux';
import { fetchApp } from '../redux/actions/appActions';
import { getUserInfo } from '../redux/actions/userActions';
import { selectApp, selectAppStatus, selectIsLoggedIn } from '../redux/selectors/selectors';

// Styles and Components
import { Colors } from '../styles';
import Button from '../components/Button';


export default function LandingPage({ navigation }) {
  const dispatch = useDispatch();
  const status = useSelector(selectAppStatus);
  const app = useSelector(selectApp);
  const isLoggedIn = useSelector(selectIsLoggedIn);
  //const [isLogged, setIsLogged] = useState(false);

  useEffect(() => {
    const fetchCookies = async () => {
      const cookies = await getAsyncStoreData('cookies');
      console.log('COOKIES', cookies);
      if (cookies) {
        dispatch(getUserInfo(cookies));
        //setIsLogged(true);
      }
    };

    fetchCookies();
  }, [dispatch]);

  useEffect(() => {
    dispatch(fetchApp());
  }, [dispatch]);

  handleStartButton = () => {
    if (isLoggedIn) {
      navigation.navigate('Main');
    } else {
      navigation.navigate('Login');
    }
  }

  return (
    <SafeAreaView style={styles.container}>
      {/* <ImageBackground source={require('../../assets/landing_background.png')} style={styles.image}></ImageBackground> */}
      <View style={styles.info}>
        <Image source={require('../../assets/braguia_logo_green.png')} style={styles.logo} />
        <Text style={styles.description}>{app.app_desc}</Text>
        <Text style={styles.text}>{app.app_landing_page_text}</Text>
      </View>
      <View style={styles.button}>
        <Button
          title="COMEÇAR"
          onPress={() => handleStartButton()}
        />
      </View>
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: Colors.white,
    alignItems: 'center',
    justifyContent: 'space-between',
  },
  info: {
    alignItems: 'center',
    justifyContent: 'center',
    marginTop: 80,
  },
  logo: {
    width: 240,
    height: 140,
  },
  description: {
    color: Colors.black,
    fontSize: 18,
    fontWeight: 'bold',
    marginTop: 50,
  },
  text: {
    color: Colors.gray500,
    fontSize: 16,
    marginTop: 30,
    marginHorizontal: 18,
  },
  button: {
    marginBottom: 60,
  },
});

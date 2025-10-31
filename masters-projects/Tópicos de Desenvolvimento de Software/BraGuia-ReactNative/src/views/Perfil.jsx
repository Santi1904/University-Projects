// Dependencies
import { Text, View, TouchableOpacity, StyleSheet, ImageBackground } from 'react-native';
import React, { useEffect } from 'react';
import Icon from 'react-native-vector-icons/MaterialCommunityIcons';
import { format } from 'date-fns';

// Styles and Components
import { Colors } from '../styles';
import Button from '../components/Button';
import appBackground from '../../assets/app_background.jpeg';

// Redux
import { useDispatch, useSelector } from 'react-redux';
import { selectUserInfo, selectIsLoggedIn } from '../redux/selectors/selectors';
import { logoutUser } from '../redux/actions/userActions';


export default function Perfil({ navigation }) {
  const dispatch = useDispatch();
  const userInfo = useSelector(selectUserInfo);
  const isLoggedIn = useSelector(selectIsLoggedIn);
  //console.log(userInfo.first_name);
  const date_joined = userInfo.date_joined;
  const joinedDate  = format(date_joined, 'dd/MM/yyyy');
  const dateLogin   = userInfo.last_login;
  const lastLogin   = format(dateLogin, 'dd/MM/yyyy HH:mm:ss');

  useEffect(() => {
    if (isLoggedIn === false) {
        navigation.navigate('LandingPage');
    }
  }, [isLoggedIn]);

  const handleLogout = () => {
    dispatch(logoutUser());
  };

  const handleSettings = () => {
    console.log('Settings pressed');
    navigation.navigate('Settings');
  };

  return (
    <View style={styles.container}>
      <ImageBackground source={appBackground} style={styles.background}>

        <View style={styles.header}>
          <TouchableOpacity style={styles.settingsButton} onPress={handleSettings}>
            <Icon name="cog" size={30} color="black" />
          </TouchableOpacity>
        </View>
        <View style={styles.iconContainer}>
          <Icon name="account-circle-outline" size={100} color={Colors.primaryColor} />
        </View>
        <Text style={styles.userName}>{userInfo.username}</Text>
        <View style={styles.separator} />

        <View style={styles.infoContainer}>
          <View style={styles.infoRow}>
            <Icon name="account" size={25} color="black" style={styles.icon} />
            <Text style={styles.infoText}>TIPO UTILIZADOR:</Text>
          </View>
          <View style={[styles.infoRow, styles.infoMargin]}>
            <Icon name="calendar" size={25} color="black" style={styles.icon} />
            <Text style={styles.infoText}>MEMBRO DESDE:</Text>
          </View>
          <View style={[styles.infoRow, styles.infoMargin]}>
            <Icon name="login" size={25} color="black" style={styles.icon} />
            <Text style={styles.infoText}>ÚLTIMO LOGIN:</Text>
          </View>
        </View>

        <View style={styles.valuesContainer}>
          <View style={[styles.valueRow, styles.valueMargin]}>
            <Text style={styles.valueText}>{userInfo.user_type}</Text>
          </View>
          <View style={[styles.valueRow, styles.valueMargin]}>
            <Text style={styles.valueText}>{joinedDate}</Text>
          </View>
          <View style={[styles.valueRow, styles.valueMargin]}>
            <Text style={styles.valueText}>{lastLogin}</Text>
          </View>
        </View>

        <View style={styles.logoutButtonContainer}>
          <Button title={"Logout"} onPress={handleLogout} />
        </View>

      </ImageBackground>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
  },
  background: {
    flex: 1,
    width: '100%',
    height: '100%',
    justifyContent: 'center',
    alignItems: 'center',
    resizeMode: 'cover',
  },
  header: {
    position: 'absolute',
    top: 10,
    right: 10,
  },
  settingsButton: {
    padding: 10,
    marginTop: 20,
    marginRight: 20,
  },
  iconContainer: {
    justifyContent: 'center',
    alignItems: 'center',
    marginTop: 10,
    marginBottom: -20,
  },
  userName: {
    marginTop: 30,
    fontSize: 20,
    fontWeight: 'bold',
    color: 'black',
  },
  separator: {
    borderBottomWidth: 1,
    borderBottomColor: Colors.primaryColor,
    width: 300,
    marginTop: 25,
    marginBottom: -45,
  },
  infoContainer: {
    marginTop: 100,
    marginStart: -150,
  },
  infoRow: {
    flexDirection: 'row',
    alignItems: 'center',
  },
  infoText: {
    fontSize: 16,
    fontWeight: 'bold',
    color: 'black',
  },
  infoMargin: {
    marginTop: 30,
  },
  icon: {
    marginRight: 10,
  },
  valuesContainer: {
    marginTop: -170,
    marginStart: 150,
  },
  valueRow: {
    flexDirection: 'row',
    alignItems: 'center',
    marginStart: 50,
  },
  valueText: {
    fontSize: 16,
    color: 'black',
  },
  valueMargin: {
    marginTop: 34,
    marginLeft: 50,
  },
  logoutButtonContainer: {
    marginTop: 120,
  }
});

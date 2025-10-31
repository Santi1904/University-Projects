// Dependencies
import { Text, View, StyleSheet, Image, TouchableOpacity , ImageBackground} from 'react-native';
import Icon from 'react-native-vector-icons/MaterialCommunityIcons';

// Styles and Components
import { Colors } from '../styles';
import appBackground from '../../assets/app_background.jpeg';

export default function Contactos({navigation}) {
  const handleContactos = () => {
    navigation.navigate('Contacts')
  };

  const handleSociais = () => {
    navigation.navigate('Socials')
  };

  const handlePartners = () => {
    navigation.navigate('Partners')
  };

  return (
    <View style={styles.container}>
      <ImageBackground source={appBackground} style={styles.background}>
        <Image source={require('../../assets/braguia_logo_green.png')} style={styles.logo} resizeMode="contain" />
        <View style={styles.buttonsContainer}>
          <TouchableOpacity onPress={handleContactos} style={styles.button}>
            <Icon name="phone" size={25} color="white" style={styles.buttonIcons} />
            <Text style={styles.buttonText}>CONTACTOS</Text>
          </TouchableOpacity>
          <TouchableOpacity onPress={handleSociais} style={styles.button}>
            <Icon name="instagram" size={25} color="white" style={styles.buttonIcons} />
            <Text style={styles.buttonText}>REDES SOCIAIS</Text>
          </TouchableOpacity>
          <TouchableOpacity onPress={handlePartners} style={styles.button}>
            <Icon name="handshake" size={25} color="white" style={styles.buttonIcons} />
            <Text style={styles.buttonText}>PARCEIROS</Text>
          </TouchableOpacity>
        </View>
      </ImageBackground>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
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
  logo: {
    width: '50%',
    height: 150,
    marginTop: -50,
  },
  buttonsContainer: {
    marginTop: 60,
    width: '70%',
    alignItems: 'center',
  },
  button: {
    backgroundColor: Colors.primaryColor,
    paddingVertical: 15,
    paddingHorizontal: 30,
    borderRadius: 10,
    marginVertical: 20,
    width: '100%',
    alignItems: 'center',
    flexDirection: 'row',
    justifyContent: 'space-evenly',
  },
  buttonText: {
    color: 'white',
    fontSize: 18,
    fontWeight: 'bold',
    textAlign: 'center',
  },
  buttonIcons: {
    marginRight: 5,
  },
});

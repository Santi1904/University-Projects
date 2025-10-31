// Dependencies
import { StyleSheet, View, Text,ImageBackground, TouchableOpacity, Linking } from 'react-native';
import Icon from 'react-native-vector-icons/AntDesign';

// Styles and Components
import { Colors } from '../styles';
import BackButton from '../components/backButton';
import appBackground from '../../assets/app_background.jpeg';


export default function SocialsInfo({ route, navigation }) {
  const { social } = route.params;

  const handleCallPress = async () => {
    try {
        await Linking.openURL(social.social_url);
      } catch (error) {
        console.error("Ocorreu um erro ao tentar abrir o link:", error);
      }
    };

    return (
        <View style={styles.container}>
            <ImageBackground source={appBackground} style={styles.background}>
            <View style={styles.backButtonContainer}>
                <BackButton />
            </View>
            <Text style={styles.detailName}>SOCIAL</Text>

            <TouchableOpacity onPress={handleCallPress}>
                <View style={styles.callNumber}>
                    <Icon name="instagram" size={80} color={Colors.primaryColor} />
                    <Text style={styles.callText}>ACEDER</Text>
                </View>
            </TouchableOpacity>

            <Text style={styles.detailLabel}>NOME: </Text>
            <Text style={styles.setSocialName}>{social.social_name}</Text>

            <Text style={styles.detailLabel}>LINK: </Text>
            <Text style={styles.setSocialLink}>{social.social_url}</Text>

          </ImageBackground>
        </View>
      );
    };

    const styles = StyleSheet.create({
      container: {
        flex: 1,
      },
      background: {
        flex: 1,
        justifyContent: 'center',
        resizeMode: 'cover',
      },
      detailName: {
        marginTop: -50,
        marginBottom: 20,
        alignSelf: 'center',
        fontSize: 24,
        fontWeight: 'bold',
        color: Colors.black,
      },
      callNumber: {
        width: 170,
        height: 170,
        justifyContent: 'center',
        alignItems: 'center',
        alignSelf: 'center',
        backgroundColor: Colors.contactsColor,
        borderRadius: 20,
      },
      callText: {
        marginTop: 15,
        fontSize: 25,
        fontWeight: 'bold',
        color: Colors.primaryColor,
      },
      detailLabel: {
        marginLeft: 40,
        marginTop: 100,
        fontSize: 18,
        fontWeight: 'bold',
        color: Colors.black,
        textAlign: 'left',
      },
      setSocialName: {
        marginLeft: 40,
        marginTop: 10,
        marginBottom: -40,
        fontSize: 16,
        color: Colors.black,
      },
      setSocialLink: {
        marginLeft: 40,
        marginTop: 10,
        fontSize: 16,
        color: Colors.black,
      },
      backButtonContainer: {
        position: 'absolute',
        top: 25,
        left: 25,
        zIndex: 1,
      },
    });

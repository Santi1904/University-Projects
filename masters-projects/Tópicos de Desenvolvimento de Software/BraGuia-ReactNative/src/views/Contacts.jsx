// Dependencies
import { StyleSheet,Image, View, FlatList, ImageBackground, SafeAreaView } from 'react-native';

// Styles and Components
import appBackground from '../../assets/app_background.jpeg';
import braguiaLogo from '../../assets/braguia_logo_green.png';
import BackButton from '../components/backButton';
import ContactCard from '../components/ContactCard';

// Redux
import { useSelector } from 'react-redux';
import { selectApp } from '../redux/selectors/selectors';


export default function Home({ navigation }) {
  const app = useSelector(selectApp);
  const contacts = app.contacts;

  const renderItem = ({ item }) => (
    <ContactCard contact={item} navigation={navigation} />
  );

  return (
    <SafeAreaView style={styles.safeArea}>
    <View style={styles.container}>
      <View style={styles.backButtonContainer}>
        <BackButton />
      </View>
      <ImageBackground source={appBackground} style={styles.background}>
        <Image source={braguiaLogo} style={styles.logo} resizeMode="contain" />
        <FlatList
          data={contacts}
          renderItem={renderItem}
          keyExtractor={(item, index) => index.toString()}
          vertical
          showsVerticalScrollIndicator={false}
          contentContainerStyle={styles.contactsContainer}
        />
      </ImageBackground>
    </View>
  </SafeAreaView>
);
};

const styles = StyleSheet.create({
  safeArea: {
    flex: 1,
  },
  container: {
    flex: 1,
  },
background: {
    flex: 1,
    width: '100%',
    justifyContent: 'center',
    alignItems: 'center',
    resizeMode: 'cover',
    paddingTop: 50,
  },
logo: {
    width: '50%',
    height: 150,
    marginBottom: 50,
},
backButtonContainer: {
    position: 'absolute',
    top: 25,
    left: 25,
    zIndex: 1,
  },
contactsContainer: {
  justifyContent: 'space-between',
  marginHorizontal: 16,
  marginTop: 50,
},
});

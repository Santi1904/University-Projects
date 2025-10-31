// Dependencies
import { StyleSheet, TouchableOpacity, View, Text, Image } from 'react-native';
import Icon from 'react-native-vector-icons/MaterialCommunityIcons';

// Styles
import { Colors } from '../styles';

export default function SocialsCard({ social, navigation }) {

    const handleSelectSocial = (social) => {
    // Verify user type
    navigation.navigate('SocialsInfo', { social });

    };

    return (
      <TouchableOpacity onPress={() => handleSelectSocial(social)}>
      <View style={styles.socialCard}>
        <View style={styles.container}>
          <Icon name="instagram" size={30} color="white" style={styles.insta} />
          <Text style={styles.name}>{social.social_name}</Text>
        </View>
      </View>
    </TouchableOpacity>
    );
};

const styles = StyleSheet.create({
socialCard: {
    width: 300,
    elevation: 8,
    backgroundColor: Colors.primaryColor, 
    borderRadius: 8,
    padding: 15,
},
container: {
  flexDirection: 'row',
  alignItems: 'center',
},
name: {
  fontSize: 20,
  fontWeight: 'bold',
  color: 'white', 
},
insta: {
  marginRight: 10,
},
});
    



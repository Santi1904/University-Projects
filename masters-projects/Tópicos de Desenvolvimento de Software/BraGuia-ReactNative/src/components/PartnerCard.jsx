// Dependencies
import { StyleSheet, TouchableOpacity, View, Text, Image } from 'react-native';
import Icon from 'react-native-vector-icons/MaterialCommunityIcons';

// Styles
import { Colors } from '../styles';

export default function PartnersCard({ partner, navigation }) {

    const handleSelectPartner = (partner) => {
    // Verify user type
    navigation.navigate('PartnerInfo', { partner });

    };

    return (
      <TouchableOpacity onPress={() => handleSelectPartner(partner)}>
      <View style={styles.socialCard}>
        <View style={styles.container}>
          <Icon name="handshake" size={30} color="white" style={styles.insta} />
          <Text style={styles.name}>{partner.partner_name}</Text>
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
    



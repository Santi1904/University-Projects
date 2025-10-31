// Dependencies
import { StyleSheet, TouchableOpacity, View, Text, Image } from 'react-native';
import Icon from 'react-native-vector-icons/MaterialCommunityIcons';

// Styles
import { Colors } from '../styles';

export default function ContactCard({ contact, navigation }) {

  const handleSelectContact = (contact) => {
    // Verify user type
    navigation.navigate('ContactInfo', { contact });

  };

  return (
    <TouchableOpacity onPress={() => handleSelectContact(contact)}>
    <View style={styles.contactCard}>
      <View style={styles.container}>
        <Icon name="phone" size={25} color="white" style={styles.phone} />
        <Text style={styles.name}>{contact.contact_name}</Text>
      </View>
    </View>
  </TouchableOpacity>
);
};

const styles = StyleSheet.create({
contactCard: {
  marginHorizontal: 10,
  marginVertical: 15,
  elevation: 8,
  backgroundColor: Colors.primaryColor, 
  borderRadius: 8,
  padding: 15,
},
container: {
  flexDirection: 'row',
  alignItems: 'center',
},
image: {
  width: 60,
  height: 60,
  borderRadius: 30, 
  marginRight: 30,
},
name: {
  fontSize: 20,
  fontWeight: 'bold',
  color: 'white', 
},
phone: {
  marginRight: 10,
},
});
    



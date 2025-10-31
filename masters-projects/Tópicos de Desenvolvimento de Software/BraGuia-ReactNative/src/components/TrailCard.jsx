// Dependencies
import { StyleSheet, TouchableOpacity, View, Text, Image } from 'react-native';
import Icon from 'react-native-vector-icons/Ionicons';

// Styles
import { Colors } from '../styles';

export default function TrailCard({ trail, navigation }) {

  const handleSelectTrail = (trail) => {
    // Verify user type
    navigation.navigate('Trail', { trail });
  };

  return (
    <TouchableOpacity
      style={styles.trailCard}
      onPress={() => handleSelectTrail(trail)}>
      <View>
        <Image source={{uri: trail.trail_img}} style={styles.trailImage} />
      </View>
      <View style={styles.trailInfo}>
        <Text style={styles.trailName}>{trail.trail_name}</Text>
        <Icon name="eye" size={24} color="black" style={{paddingTop: 4}} />
      </View>
    </TouchableOpacity>
  );
}

const styles = StyleSheet.create({
  trailCard: {
    backgroundColor: Colors.white,
    padding: 10,
    borderRadius: 10,
    marginRight: 16,
    width: 180,
  },
  trailImage: {
    width: 160,
    height: 160,
    borderRadius: 10,
  },
  trailInfo: {
    flexDirection: 'row',
    justifyContent: 'space-between',
    alignItems: 'baseline',
  },
  trailName: {
    fontSize: 18,
    color: Colors.black,
    fontWeight: 'bold',
    marginTop: 10,
    marginLeft: 4,
  },
});

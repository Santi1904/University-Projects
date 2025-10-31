// Dependencies
import { StyleSheet, TouchableOpacity } from 'react-native';
import Icon from 'react-native-vector-icons/Ionicons';

export default function FavButton() {
  const handleLike = () => {
    // Implement like functionality
  };

  return (
    <TouchableOpacity style={styles.favButton} onPress={handleLike}>
      <Icon name="heart-outline" size={35} color="black" />
    </TouchableOpacity>
  );
}

const styles = StyleSheet.create({
  favButton: {
    position: 'absolute',
    top: 25,
    right: 25,
  },
});

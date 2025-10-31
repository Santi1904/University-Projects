import { StyleSheet, Text, TouchableOpacity } from 'react-native';
import { Colors, Buttons } from '../styles';

const Button = ({title, onPress}) => {
  return (
    <TouchableOpacity style={styles.buttonContainer} onPress={onPress}>
      <Text style={styles.buttonText}>{title}</Text>
    </TouchableOpacity>
  );
};

const styles = StyleSheet.create({
  buttonContainer: {
    ...Buttons.smallRounded,
    backgroundColor: Colors.white,
  },
  buttonText: {
    color: Colors.black,
    textAlign: 'center',
    fontSize: 14,
    fontWeight: 'bold',
  },
});

export default Button;
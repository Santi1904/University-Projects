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
    backgroundColor: Colors.primaryColor,
  },
  buttonText: {
    color: Colors.white,
    textAlign: 'center',
    fontSize: 16,
    fontWeight: 'bold',
  },
});

export default Button;

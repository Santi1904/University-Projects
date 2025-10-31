// Dependencies
import { useNavigation } from '@react-navigation/native';
import React from 'react';
import { StyleSheet, TouchableOpacity } from 'react-native';
import Icon from 'react-native-vector-icons/Ionicons';

export default function BackButton() {
  const navigation = useNavigation();

  return (
    <TouchableOpacity style={styles.backButton} onPress={() => navigation.goBack()}>
      <Icon name="arrow-back" size={35} color="black" />
    </TouchableOpacity>
  );
}

const styles = StyleSheet.create({
  backButton: {
    marginTop: 25,
    marginLeft: 25,
    position: 'absolute',
  },
});

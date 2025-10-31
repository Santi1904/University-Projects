// Dependencies
import { useState } from 'react';
import { Text, View, StyleSheet, Image, Switch } from 'react-native';
import { useTheme } from '../styles/themeContext';

// Styles and Components
import { Colors } from '../styles';

export default function Settings() {
  const { isDarkMode, toggleTheme } = useTheme();
  const [notificationsEnabled, setNotificationsEnabled] = useState(false);
  const [locationEnabled, setLocationEnabled] = useState(false);

  const toggleNotifications = () => setNotificationsEnabled(previousState => !previousState);
  const toggleLocation = () => setLocationEnabled(previousState => !previousState);

  return (
    <View style={[styles.container, { backgroundColor: isDarkMode ? '#333' : '#fff' }]}>
      <Image source={require('../../assets/braguia_logo_green.png')} style={styles.logo} resizeMode="contain" />

      <View style={styles.switchContainer}>
        <Text style={[styles.label, { color: isDarkMode ? '#fff' : '#000' }]}>Ativar/Desativar Notificações</Text>
        <Switch
          trackColor={{ false: "#767577", true: Colors.primaryColor }}
          thumbColor={notificationsEnabled ? Colors.primaryColor : "#f4f3f4"}
          onValueChange={toggleNotifications}
          value={notificationsEnabled}
        />
      </View>
      <View style={styles.switchContainer}>
        <Text style={[styles.label, { color: isDarkMode ? '#fff' : '#000' }]}>Ativar/Desativar Localização</Text>
        <Switch
          trackColor={{ false: "#767577", true: Colors.primaryColor }}
          thumbColor={locationEnabled ? Colors.primaryColor : "#f4f3f4"}
          onValueChange={toggleLocation}
          value={locationEnabled}
        />
      </View>
      <View style={styles.switchContainer}>
        <Text style={[styles.label, { color: isDarkMode ? '#fff' : '#000' }]}>Modo Escuro</Text>
        <Switch
          trackColor={{ false: "#767577", true: Colors.primaryColor }}
          thumbColor={isDarkMode ? Colors.primaryColor : "#f4f3f4"}
          onValueChange={toggleTheme}
          value={isDarkMode}
        />
      </View>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
  },
  logo: {
    width: '50%',
    height: 150,
    marginTop: 50,
    marginBottom: 60,
  },
  switchContainer: {
    flexDirection: 'row',
    justifyContent: 'space-between',
    alignItems: 'center',
    marginVertical: 10,
    marginTop: 30,
    width: '80%',
  },
  label: {
    fontSize: 16,
    fontWeight: 'bold',
  },
});

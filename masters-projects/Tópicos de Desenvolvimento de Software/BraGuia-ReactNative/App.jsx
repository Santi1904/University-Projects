import React from 'react';
import { NavigationContainer } from '@react-navigation/native';
import { createBottomTabNavigator } from '@react-navigation/bottom-tabs';
import { createNativeStackNavigator } from '@react-navigation/native-stack';
import { SafeAreaProvider } from 'react-native-safe-area-context';
import { enableScreens } from 'react-native-screens';
import Icon from 'react-native-vector-icons/Ionicons';
import { ThemeProvider, useTheme } from './src/styles/themeContext';

// Screens
import LandingPage from './src/views/LandingPage';
import Home from './src/views/Home';
import Perfil from './src/views/Perfil';
import AppContacts from './src/views/AppContacts';
import Trail from './src/views/Trail';
import Pin from './src/views/Pin';
import Settings from './src/views/Settings';
import Login from './src/views/Login';
import Contacts from './src/views/Contacts';
import ContactInfo from './src/views/ContactInfo';
import Socials from './src/views/Socials';
import SocialsInfo from './src/views/SocialInfo';
import Partners from './src/views/Partners';
import PartnerInfo from './src/views/PartnerInfo';
import Premium from './src/views/Premium';

enableScreens();
const Tab = createBottomTabNavigator();
const Stack = createNativeStackNavigator();

function HomeStack() {
  return (
    <Stack.Navigator>
      <Stack.Screen name="HomeStack" component={Home} options={{headerShown: false}} />
      <Stack.Screen name="Trail" component={Trail} options={{headerShown: false}} />
      <Stack.Screen name="Pin" component={Pin} options={{headerShown: false}} />
      <Stack.Screen name="Premium" component={Premium} options={{headerShown: false}} />
    </Stack.Navigator>
  );
}

function AppContactsStack() {
  return (
    <Stack.Navigator>
      <Stack.Screen name="AppContactsStack" component={AppContacts} options={{headerShown: false}} />
      <Stack.Screen name="Contacts" component={Contacts} options={{headerShown: false}} />
      <Stack.Screen name="ContactInfo" component={ContactInfo} options={{headerShown: false}} />
      <Stack.Screen name="Socials" component={Socials} options={{headerShown: false}} />
      <Stack.Screen name="SocialsInfo" component={SocialsInfo} options={{headerShown: false}} />
      <Stack.Screen name="Partners" component={Partners} options={{headerShown: false}} />
      <Stack.Screen name="PartnerInfo" component={PartnerInfo} options={{headerShown: false}} />
    </Stack.Navigator>
  );
}


function App() {
  // const isDarkMode = useColorScheme() === 'dark';

  // const backgroundStyle = {
  //   backgroundColor: isDarkMode ? Colors.darker : Colors.lighter,
  // };

  return (
    <ThemeProvider>
    <SafeAreaProvider>
      <NavigationContainer>
        <Stack.Navigator initialRouteName="LandingPage">
          <Stack.Screen name="LandingPage" component={LandingPage} options={{headerShown: false}} />
          <Stack.Screen name="Login" component={Login} options={{headerShown: false}} />
          <Stack.Screen name="Main" options={{headerShown: false}}>
            {() => (
              <Tab.Navigator
                initialRouteName="Home"
                screenOptions={({ route }) => ({
                  tabBarIcon: ({ focused }) => {
                    let iconName = '';

                    if (route.name === 'Home') {
                      iconName = focused ? 'home' : 'home-outline';
                    } else if (route.name === 'Perfil') {
                      iconName = focused ? 'person' : 'person-outline';
                    } else if (route.name === 'Contactos') {
                      iconName = focused ? 'people' : 'people-outline';
                    }

                    return <Icon name={iconName} size={30} color="black" />;
                  },
                  tabBarActiveTintColor: 'black',
                  tabBarInactiveTintColor: 'gray',
                })}>
                <Tab.Screen
                  name="Home"
                  component={HomeStack}
                  options={{headerShown: false}}
                />
                <Tab.Screen
                  name="Contactos"
                  component={AppContactsStack}
                  options={{headerShown: false}}
                />
                <Tab.Screen
                  name="Perfil"
                  component={Perfil}
                  options={{headerShown: false}}
                />
              </Tab.Navigator>
            )}
          </Stack.Screen>
          <Stack.Screen name="Settings" component={Settings} />
        </Stack.Navigator>
      </NavigationContainer>
    </SafeAreaProvider>
    </ThemeProvider>
  );
}

export default App;

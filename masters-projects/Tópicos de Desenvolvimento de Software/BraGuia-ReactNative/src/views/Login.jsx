// Dependencies
import { StyleSheet, View, Keyboard ,ImageBackground, Image, TextInput, Alert } from 'react-native';
import { useEffect, useState } from 'react';
import Icon from 'react-native-vector-icons/MaterialCommunityIcons';

// Redux
import { useDispatch, useSelector } from 'react-redux';
import { login } from '../redux/actions/userActions';
import { selectUserStatus } from '../redux/selectors/selectors';

// Styles and Components
import { Colors } from '../styles';
import Button from '../components/LoginButton';
import loginBackground from '../../assets/login_background.jpg';
import braguiaLogo from '../../assets/braguia_logo.png';


export default function Login({ navigation }) {
    const dispatch = useDispatch();
    const userStatus = useSelector(selectUserStatus);
    const [username, setUsername] = useState('');
    const [password, setPassword] = useState('');
    const [contenHeight, setContentHeight] = useState(0);

    useEffect(() => {
      const keyboardDidHideListener = Keyboard.addListener('keyboardDidHide', () => {
        setContentHeight(0);
      });

      return () => {
        keyboardDidHideListener.remove();
      };
    }, []);

    useEffect(() => {
      if (userStatus === 'success') {
        // Alert.alert('Sucesso','Login efetuado com sucesso!');
        navigation.navigate('Main');
      } else if (userStatus === 'failed') {
        Alert.alert('Login Incorreto','Credenciais incorretas. Tente novamente.');
      }
    }, [userStatus]);

    const handleStartButton = async () => {
      if (username === '' || password === '') {
          Alert.alert('Atenção','Preencha todos os campos.');
          return;
      }

      dispatch(login(username, password));
    };


    return (
        <View style={styles.container}>
            <ImageBackground source={loginBackground} style={styles.background}>
                <View style={styles.inner}>
                    <Image source={braguiaLogo} style={styles.logo} />
                    <View style={styles.content}>
                        <View style={styles.usernameContainer}>
                            <Icon name="account" size={25} color="white" style={styles.userIcon} />
                            <TextInput
                                style={styles.inputUsername}
                                placeholder="Username"
                                value={username}
                                onChangeText={setUsername}
                                placeholderTextColor="rgba(0, 0, 0, 0.7)"
                            />
                        </View>
                        <View style={styles.passwordContainer}>
                            <Icon name="lock" size={25} color="white" style={styles.passIcon} />
                            <TextInput
                                style={styles.inputPassword}
                                placeholder="Password"
                                value={password}
                                onChangeText={setPassword}
                                secureTextEntry
                                placeholderTextColor="rgba(0, 0, 0, 0.7)"
                            />
                        </View>
                    </View>
                    <View style={styles.button}>
                        <Button
                            title="LOGIN"
                            onPress={handleStartButton}
                        />
                    </View>
                </View>
            </ImageBackground>
        </View>
    );
}

const styles = StyleSheet.create({
    container: {
        flex: 1,
        backgroundColor: Colors.white,
    },
    background: {
        flex: 1,
        width: '100%',
        height: '100%',
        justifyContent: 'center',
        alignItems: 'center',
        resizeMode: 'cover',
    },
    inner: {
        justifyContent: 'center',
        alignItems: 'center',
        padding: 20,
    },
    logo: {
        width: 240,
        height: 140,
        marginBottom: 80,
        marginTop: -20,
    },
    content: {
        width: '100%',
        alignItems: 'center',
        justifyContent: 'center',
    },

    usernameContainer: {
        flexDirection: 'row',
        alignItems: 'center',
        backgroundColor: 'transparent',
        borderRadius: 20,
        width: 300,
        height: 40,
        marginBottom: 20,
        paddingLeft: 10,
        borderColor: 'white',
        borderWidth: 2,
    },
    userIcon: {
        marginRight: 10,
    },
    inputUsername: {
        flex: 1,
        color: 'white',
    },
    passwordContainer: {
        flexDirection: 'row',
        alignItems: 'center',
        backgroundColor: 'transparent',
        borderRadius: 20,
        width: 300,
        height: 40,
        marginBottom: 20,
        paddingLeft: 10,
        borderColor: 'white',
        borderWidth: 2,
    },
    passIcon: {
        marginRight: 10,
    },

    inputPassword: {
        flex: 1,
        color: 'white',
    },
    button: {
        marginTop: 50,
        marginBottom: 20,
        width: 200,
    },
});

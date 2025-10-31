import AsyncStorage from '@react-native-async-storage/async-storage';
import {
    LOGIN_SUCCESS,
    LOGIN_FAILURE,
    USER_INFO,
    LOGOUT,
} from '../../constants';

import API from '../../utils/api';
import { setAsyncStoreData } from '../../utils/async-storage';
import { getAsyncStoreData } from '../utils/async-storage';


export const loginSuccess = () => ({
  type: LOGIN_SUCCESS,
});

export const loginFailure = (error) => ({
  type: LOGIN_FAILURE,
  payload: { error },
});

export const user_info = (user_info) => ({
  type: USER_INFO,
  payload: { user_info },
});

export const logout = () => ({
  type: LOGOUT,
});

function parseCookies(cookieString) {
  const cookies = {};
  const cookiePairs = cookieString[0].split(/,(?=\s*[^;]+=[^;])/);

  cookiePairs.forEach(pair => {
    const [name, ...rest] = pair.split('=');
    const value = rest.join('=').trim();

    if (name.trim() === 'csrftoken') {
      cookies.csrftoken = value;
    } else if (name.trim() === 'sessionid') {
      cookies.sessionid = value;
    }
  });

  return cookies;
}

export const getUserInfo = (cookies) => {
  return async (dispatch) => {
    try {
      const config = {
        headers: {
          Cookie: cookies,
        }
      };

      const response = await API.get('/user', config);
      if (response.status !== 200) {
        throw new Error('Request failed with status code ' + response.status);
      }

      console.log('GET USER INFO', response.data);

      dispatch(user_info(response.data));
    } catch (error) {
      console.log('ERROR GET USER INFO',error.message);
    }
  };
};

export const login = (username, password) => {
  return async (dispatch) => {
    try {
      const body = {
        username: username,
        password: password,
      };

      console.log("Started login request");

      const response = await API.post('/login', body);
      if (response.status !== 200) {
        throw new Error('Request failed with status code ' + response.status);
      }

      const cookies = response.headers['set-cookie'];
      const parsedCookies = parseCookies(cookies);
      if (!parsedCookies.csrftoken || !parsedCookies.sessionid) {
          throw new Error('Failed to parse cookies');
      }

      const csrftoken = parsedCookies.csrftoken.split(';')[0];
      const sessionid = parsedCookies.sessionid.split(';')[0];
      const cookies_api = `csrftoken=${csrftoken}; sessionid=${sessionid}`;
      await setAsyncStoreData('cookies', cookies_api);

      dispatch(getUserInfo(cookies_api));

      dispatch(loginSuccess());
    } catch (error) {
      dispatch(loginFailure(error.message));
    }
  };
};

export const logoutUser = () => {
  return async (dispatch) => {
    try {
      const cookies = await AsyncStorage.getItem('cookies');
      const sessionid = cookies.split(';')[1].trim();

      const config = {
        headers: {
          Cookie : sessionid,
        }
      };

      const response = await API.post('/logout', config);
      if (response.status !== 200) {
        throw new Error('Request failed with status code ' + response.status);
      }

      dispatch(logout());

      await AsyncStorage.removeItem('cookies');

      console.log('LOGOUT SUCCESS');
    } catch (error) {
      console.log('ERRO NO LOGOUT',error.message);
    }
  };
};



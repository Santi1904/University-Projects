import AsyncStorage from '@react-native-async-storage/async-storage';

export const getAsyncStoreData = async (key) => {
  try {
    const value = await AsyncStorage.getItem(key);
    return value;
  } catch (e) {
    console.log('Error retrieving data from AsyncStorage:', e);
  }
}

export const setAsyncStoreData = async (key, value) => {
  try {
    await AsyncStorage.setItem(key, value);
  } catch (e) {
    console.log('Error storing data in AsyncStorage:', e);
  }
}

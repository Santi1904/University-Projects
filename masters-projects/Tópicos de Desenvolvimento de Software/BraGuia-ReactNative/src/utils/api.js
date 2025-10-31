import axios from 'axios';

const BASE_URL = 'https://e70c-193-137-92-72.ngrok-free.app';

const API = axios.create({
  withCredentials: false,
  baseURL: BASE_URL,
  responseType: 'json',
  headers: {
    'content-Type': 'application/json',
  },
});

export async function getApiTrails() {
  try {
    const response = await API.get('/trails');
    // console.log('response', response);
    return response.data;
  } catch (error) {
    console.error('Error fetching trails', error);
  }
}

export default API;

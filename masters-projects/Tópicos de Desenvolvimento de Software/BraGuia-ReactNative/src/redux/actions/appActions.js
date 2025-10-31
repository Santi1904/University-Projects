import {
  FETCH_APP_STARTED,
  FETCH_APP_SUCCEEDED,
  FETCH_APP_FAILED,
} from '../../constants';
import API from '../../utils/api';

export const fetchAppStarted = () => ({
  type: FETCH_APP_STARTED,
});

export const fetchAppSucceeded = app => ({
  type: FETCH_APP_SUCCEEDED,
  payload: app,
});

export const fetchAppFailed = error => ({
  type: FETCH_APP_FAILED,
  payload: error,
});

export const fetchApp = () => {
  return async dispatch => {
    dispatch(fetchAppStarted());

    try {
      const response = await API.get('/app');
      const app = response.data[0];
      dispatch(fetchAppSucceeded(app));
    } catch (error) {
      console.error('Error fetching app', error);
      dispatch(fetchAppFailed(error));
    }
  };
}

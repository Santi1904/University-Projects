import {
  FETCH_TRAILS_STARTED,
  FETCH_TRAILS_SUCCEEDED,
  FETCH_TRAILS_FAILED,
  TRAILS_CHANGE,
} from '../../constants';
import API from '../../utils/api';

export const fetchTrailsStarted = () => ({
  type: FETCH_TRAILS_STARTED,
});

export const fetchTrailsSucceeded = trails => ({
  type: FETCH_TRAILS_SUCCEEDED,
  payload: trails,
});

export const fetchTrailsFailed = error => ({
  type: FETCH_TRAILS_FAILED,
  payload: error,
});

export const fetchTrails = () => {
  return async dispatch => {
    dispatch(fetchTrailsStarted());

    try {
      const response = await API.get('/trails');
      const trails = response.data;
      dispatch(fetchTrailsSucceeded(trails));
    } catch (error) {
      console.error('Error fetching trails', error);
      dispatch(fetchTrailsFailed(error));
    }
  };
};

export const setTrails = trails => ({
  type: TRAILS_CHANGE,
  payload: trails,
});

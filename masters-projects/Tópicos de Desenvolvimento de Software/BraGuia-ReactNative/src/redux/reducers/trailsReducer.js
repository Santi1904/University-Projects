import {
  FETCH_TRAILS_STARTED,
  FETCH_TRAILS_SUCCEEDED,
  FETCH_TRAILS_FAILED,
  TRAILS_CHANGE,
} from '../../constants';

const initialState = {
  status: 'uninitialized',
  trails: [],
  error: null,
};

const trailsReducer = (state = initialState, action) => {
  switch (action.type) {
    case FETCH_TRAILS_STARTED:
      return {
        ...state,
        status: 'loading',
      };

    case FETCH_TRAILS_SUCCEEDED:
      return {
        ...state,
        status: 'succeeded',
        trails: action.payload,
      };

    case FETCH_TRAILS_FAILED:
      return {
        ...state,
        status: 'failed',
        error: action.payload,
      };

    case TRAILS_CHANGE:
      return {
        ...state,
        trails: action.payload,
      };

    default:
      return state;
  }
};

export default trailsReducer;

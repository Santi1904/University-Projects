import {
  FETCH_APP_STARTED,
  FETCH_APP_SUCCEEDED,
  FETCH_APP_FAILED,
} from '../../constants';

const initialState = {
  status: 'uninitialized',
  app: {},
  error: null,
};

const appReducer = (state = initialState, action) => {
  switch (action.type) {
    case FETCH_APP_STARTED:
      return {
        ...state,
        status: 'loading',
      };

    case FETCH_APP_SUCCEEDED:
      return {
        ...state,
        status: 'succeeded',
        app: action.payload,
      };

    case FETCH_APP_FAILED:
      return {
        ...state,
        status: 'failed',
        error: action.payload,
      };

    default:
      return state;
  }
}

export default appReducer;

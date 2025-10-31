import {configureStore} from '@reduxjs/toolkit';

import appReducer from '../reducers/appReducer';
import trailsReducer from '../reducers/trailsReducer';
import userReducer from '../reducers/userReducer';

const store = configureStore({
  reducer: {
    app: appReducer,
    trails: trailsReducer,
    user: userReducer,
  },
});

export default store;

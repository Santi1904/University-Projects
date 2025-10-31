import {LOGIN_SUCCESS,
        LOGIN_FAILURE,
        USER_INFO,
        LOGOUT,
} from '../../constants';

const initialState = {
  status: 'request',
  isLoggedIn: false,
  error: null,
  user_info: {},
};

const userReducer = (state = initialState, action) => {
  switch (action.type) {

    case LOGIN_SUCCESS:
        return {
            ...state,
            status: 'success',
            isLoggedIn: true
        };

    case LOGIN_FAILURE:
        return {
            ...state,
            status: 'failed',
            error: action.payload.error
        };

    case USER_INFO:
        return {
            ...state,
            user_info: action.payload.user_info,
            isLoggedIn: true
        };

    case LOGOUT:
        return {
            ...state,
            status : 'request',
            isLoggedIn: false
        };

    default:
      return state;
  }
};

export default userReducer;

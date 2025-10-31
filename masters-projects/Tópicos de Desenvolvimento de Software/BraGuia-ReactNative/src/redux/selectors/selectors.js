// APP
export const selectAppStatus = state => state.app.status;
export const selectApp = state => state.app.app;

// TRAILS
export const selectTrailsStatus = state => state.trails.status;
export const selectTrails = state => state.trails.trails;

// USER
export const selectUserStatus = state => state.user.status;
export const selectCookies = state => state.user.cookies;
export const selectUserInfo = state => state.user.user_info;
export const selectUserType = state => state.user.user_info.user_type;
export const selectIsLoggedIn = state => state.user.isLoggedIn;

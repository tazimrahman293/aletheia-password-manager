import { useState } from 'react';

/**
 *  Custok hook for Setting a new token on Login
 * @returns an object that contains the token and saveToken set to the setToken property name.
 */
export default function useToken() {
  const getToken = () => {
    // Can change to Session Storage if need be
    const tokenString = sessionStorage.getItem('token');
    const userToken = JSON.parse(tokenString);
    return userToken
  };

  const [token, setToken] = useState(getToken());

  const saveToken = userToken => {
    sessionStorage.setItem('token', JSON.stringify(userToken));
    setToken(userToken); 
  };

  return {
    setToken: saveToken,
    token
  }
}
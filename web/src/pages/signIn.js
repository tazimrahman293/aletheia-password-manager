import React from 'react';
import ScrollToTop from '../components/ScrollToTop';
import SignIn from '../components/SignIn';
import { Helmet } from "react-helmet";

/**
 * 
 * @returns SignIn page from component
 */
const SignInPage = ({ setToken }) => {

  return (
    <>
      <Helmet>
        <meta charSet="utf-8" />
        <title>Sign In</title>
      </Helmet>
      <ScrollToTop />
      <SignIn setToken={setToken}/>
    </>
  )
}

export default SignInPage
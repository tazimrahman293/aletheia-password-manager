import React from 'react';
import ScrollToTop from '../components/ScrollToTop';
import SignUp from '../components/SignUp';
import { Helmet } from "react-helmet";

/**
 * 
 * @returns SignUp page from component
 */
const SignUpPage = () => {

  return (
    <>
      <Helmet>
        <meta charSet="utf-8" />
        <title>Sign Up</title>
      </Helmet>
      <ScrollToTop />
      <SignUp />
    </>
  )
}

export default SignUpPage
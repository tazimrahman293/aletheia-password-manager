import React from 'react';
import ScrollToTop from '../components/ScrollToTop';
import { Helmet } from "react-helmet";
import CreateAccount from '../components/CreateAccount';

/**
 * 
 * @returns SignUp page from component
 */
const CreateAccountPage = () => {

  return (
    <>
      <Helmet>
        <meta charSet="utf-8" />
        <title>Create Account</title>
      </Helmet>
      <ScrollToTop />
      <CreateAccount />
    </>
  )
}

export default CreateAccountPage
import React from 'react'
import ScrollToTop from '../components/ScrollToTop'
import { Helmet } from "react-helmet";
import ServerDown from './../components/Error/serverDown';
/**
 * 
 * @returns 500 page from component
 */
const ServerDownPage = () => {

  return (
    <>
      <Helmet>
        <meta charSet="utf-8" />
        <title>500 | Server Down</title>
      </Helmet>
      <ScrollToTop />
      <ServerDown/>
    </>
  )
}

export default ServerDownPage
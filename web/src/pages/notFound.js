import React, {useState} from 'react'
import ScrollToTop from '../components/ScrollToTop'
import { Helmet } from "react-helmet";
import NotFound from './../components/Error/404'
/**
 * 
 * @returns 404 page from component
 */
const NotFoundPage = () => {

  const [isOpen, setIsOpen] = useState(false)

  const toggle = () => {
    setIsOpen(!isOpen)
  }

  return (
    <>
      <Helmet>
        <meta charSet="utf-8" />
        <title>404 | Page Not Found</title>
      </Helmet>
      <ScrollToTop />
      <NotFound/>
    </>
  )
}

export default NotFoundPage
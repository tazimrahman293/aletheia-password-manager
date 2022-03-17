import React, {useState} from 'react'
import ScrollToTop from '../components/ScrollToTop'
import NavbarUser from './../components/NavbarUser'
import SidebarUser from './../components/SidebarUser'
import { Helmet } from "react-helmet";
import Settings from './../components/Settings'
/**
 * 
 * @returns Settings page from component
 */
const SettingsPage = () => {

  const [isOpen, setIsOpen] = useState(false)

  const toggle = () => {
    setIsOpen(!isOpen)
  }

  return (
    <>
      <Helmet>
        <meta charSet="utf-8" />
        <title>Settings</title>
      </Helmet>
      <NavbarUser toggle={toggle} />
      <SidebarUser isOpen={isOpen} toggle={toggle} />
      <ScrollToTop />
      <Settings/>
    </>
  )
}

export default SettingsPage
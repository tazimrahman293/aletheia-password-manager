import React, { useState } from 'react'
import ScrollToTop from '../components/ScrollToTop'
import NavbarUser from '../components/NavbarUser'
import SidebarUser from '../components/SidebarUser'
import { Helmet } from "react-helmet";
import Dashboard from '../components/Dashboard';
// import Demo from '../components/demo'
/**
 * 
 * @returns Dashboard page from component
 */
const DashboardPage = () => {

  const [isOpen, setIsOpen] = useState(false)

  const toggle = () => {
    setIsOpen(!isOpen)
  }

  return (
    <>
      <Helmet>
        <meta charSet="utf-8" />
        <title>Dashboard</title>
      </Helmet>
      <NavbarUser toggle={toggle} />
      <SidebarUser isOpen={isOpen} toggle={toggle} />
      {/* <Demo/> */}
      <ScrollToTop />
      <Dashboard/>
    </>
  )
}

export default DashboardPage
import React, { useState } from 'react'
import ScrollToTop from '../components/ScrollToTop'
import NavbarUser from '../components/NavbarUser'
import SidebarUser from '../components/SidebarUser'
import { Helmet } from "react-helmet";
import Dashboard from '../components/Dashboard';

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
      <ScrollToTop />
      <Dashboard/>
    </>
  )
}

export default DashboardPage
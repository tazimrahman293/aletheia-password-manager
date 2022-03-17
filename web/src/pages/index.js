import React, { useState } from 'react'
import HomeSection from '../components/HomeSection'
import Navbar from '../components/Navbar'
import Sidebar from '../components/Sidebar'
import DataSection from '../components/DataSection'
import { dataAbout, dataFeautures } from '../components/DataSection/Data'
import Team from '../components/Team'
import { Helmet } from "react-helmet";

/**
 * This is the main page which uses all the components and renders the App
 * @returns 
 */
const Home = () => {
  // debugger
  const [isOpen, setIsOpen] = useState(false)

  const toggle = () => {
    setIsOpen(!isOpen)
  }

  return (
    <>
      <Helmet>
        <meta charSet="utf-8" />
        <title>Home</title>
      </Helmet>
      <Sidebar isOpen={isOpen} toggle={toggle} />
      <Navbar toggle={toggle} />
      <HomeSection />
      <DataSection {...dataAbout} />
      <DataSection {...dataFeautures} />
      <Team />
    </>
  );
}

export default Home
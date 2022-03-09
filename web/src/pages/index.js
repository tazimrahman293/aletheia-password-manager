import React, {useState} from 'react'
import HomeSection from '../components/HomeSection'
import Navbar from '../components/Navbar'
import Sidebar from '../components/Sidebar'
import DataSection from '../components/DataSection'
import { dataAbout, dataTeam } from '../components/DataSection/Data'
import Features from '../components/Features'

const Home = () => {
  debugger
    const [isOpen, setIsOpen] = useState(false)

    const toggle = () => {
        setIsOpen(!isOpen)
    }

  return (
    <>
      <Sidebar isOpen={isOpen} toggle={toggle}/>
      <Navbar toggle={toggle}/>
      <HomeSection/>
      <DataSection {...dataAbout}/>
      <Features/>
      <DataSection {...dataTeam}/>
    </>
  );
}

export default Home
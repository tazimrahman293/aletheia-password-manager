import React, {useState} from 'react'
import HomeSection from '../components/HomeSection'
import Navbar from '../components/Navbar'
import Sidebar from '../components/Sidebar'
import DataSection from '../components/DataSection'
import { dataAbout, dataFeautures } from '../components/DataSection/Data'
import Team from '../components/Team'

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
      <DataSection {...dataFeautures}/>
      <Team/>
    </>
  );
}

export default Home
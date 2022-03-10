import React, {useEffect, useState} from 'react';
import { FaBars } from 'react-icons/fa';
import { Nav, NavContainer, NavLogo, IconMobile, NavMenu, NavItems, NavLinks, NavButton, NavButtonLink, NavLinkRouter } from './NavbarElements';
import { animateScroll as scroll } from 'react-scroll';

const Navbar = ({ toggle }) => {
    const [scrollNav, setScrollNav] = useState(false)

    const changeNav = () => {
        if(window.scrollY >= 80) {
            setScrollNav(true)
        } else {
            setScrollNav(false)
        }
    }

    useEffect(() => {
        window.addEventListener('scroll', changeNav)
    }, [])

    const toggleHome = () => {
        scroll.scrollToTop()
    }

    return (
        <>
            <Nav scrollNav={scrollNav}>
                <NavContainer>
                    <NavLogo to='/' onClick={toggleHome}>
                        Aletheia
                    </NavLogo>
                    <IconMobile onClick={toggle}>
                        <FaBars />
                    </IconMobile>
                    <NavMenu>
                        <NavItems>
                            <NavLinks to='about'  smooth={true} duration={500} spy={true} exact='true' offset={-80}>About</NavLinks>
                        </NavItems>
                        <NavItems>
                            <NavLinks to='features' smooth={true} duration={500} spy={true} exact='true' offset={-80}>Features</NavLinks>
                        </NavItems>
                        <NavItems>
                            <NavLinks to='team' smooth={true} duration={500} spy={true} exact='true' offset={-80}>Team</NavLinks>
                        </NavItems>
                        <NavItems>
                            <NavLinkRouter to='/signUp'>Sign Up</NavLinkRouter>
                        </NavItems>
                    </NavMenu>
                    <NavButton>
                        <NavButtonLink to='/signIn'>Sign In</NavButtonLink>
                    </NavButton>
                </NavContainer>
            </Nav>

        </>
    )
}

export default Navbar;
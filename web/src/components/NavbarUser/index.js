import React from 'react';
import { FaBars } from 'react-icons/fa';
import { Nav, NavContainer, IconMobile, NavMenu, NavItems, NavButton, NavButtonLink } from './../Navbar/NavbarElements';
import { NavLogoRouter } from '../Navbar/NavbarElements';
import { NavLinkR } from './NavbarUserElements';

/**
 * 
 * @param {toggle} function used to keep track of clickEvents on Aletheia logo
 * @returns NavBarUser
 */
const NavbarUser = ({ toggle }) => {

    return (
        <>
            <Nav>
                <NavContainer>
                    <NavLogoRouter to='/' id='homePage'>
                        Aletheia
                    </NavLogoRouter>
                    <IconMobile onClick={toggle}>
                        <FaBars style={{color: '#F56300'}} />
                    </IconMobile>
                    <NavMenu>
                        <NavItems>
                            <NavLinkR to='/user' id='user'>User</NavLinkR>
                        </NavItems>
                        <NavItems>
                            <NavLinkR to='/dashboard' id='dashboard'>Dashboard</NavLinkR>
                        </NavItems>
                        <NavItems>
                            <NavLinkR to='/settings' id='settings'>Settings</NavLinkR>
                        </NavItems>
                        <NavItems>
                            <NavLinkR to='/signUp' id='signUp'>Sign Up</NavLinkR>
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

export default NavbarUser;
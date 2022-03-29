import React from 'react';
import { FaBars } from 'react-icons/fa';
import { Nav, NavContainer, IconMobile, NavMenu, NavItems, NavButton, NavButtonLink } from './../Navbar/NavbarElements';
import { NavLogoRouter } from '../Navbar/NavbarElements';
import { NavLinkR } from './NavbarUserElements';
import useToken from '../UseToken/useToken';
import deleteToken from '../UseToken/deleteToken';
/**
 * 
 * @param {toggle} function used to keep track of clickEvents on Aletheia logo
 * @returns NavBarUser
 */
const NavbarUser = ({ toggle }) => {
    const { token } = useToken();

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
                    </NavMenu>
                    <NavButton>
                    {token ? <NavButtonLink onClick={deleteToken} to='/'>Sign Out</NavButtonLink> : <NavButtonLink to='/signIn'>Sign In</NavButtonLink>}
                    </NavButton>
                </NavContainer>
            </Nav>

        </>
    )
}

export default NavbarUser;
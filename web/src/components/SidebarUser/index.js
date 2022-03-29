import React from 'react'
import { SidebarContainer, Icon, CrossIcon, SideBarWrapper, SidebarMenu, SidebarButton, SidebarButtonRouter, SidebarLinkRouter} from './../Sidebar/SidebarElements'
import useToken from '../UseToken/useToken';
import deleteToken from '../UseToken/deleteToken';

/**
 * 
 * @param {isOpen, toggle} function used to keep track of clickEvents on Sidebar and HomeButton
 * @returns SidebarUser
 */
const SidebarUser = ({isOpen, toggle}) => {
    const { token } = useToken();

    return (
        <SidebarContainer isOpen={isOpen} onClick={toggle}>
            <Icon onClick={toggle}>
                <CrossIcon />
            </Icon>
            <SideBarWrapper>
                <SidebarMenu>
                    <SidebarLinkRouter to='/' id='homePage'>Home</SidebarLinkRouter>
                    <SidebarLinkRouter to='/user' id='user' >User</SidebarLinkRouter>
                    <SidebarLinkRouter to='/dashboard' id='dashboard'>Dashboard</SidebarLinkRouter>
                </SidebarMenu>
                <SidebarButton>
                {token ? <SidebarButtonRouter onClick={deleteToken} to='/'>Sign Out</SidebarButtonRouter> : <SidebarButtonRouter to='/signIn'>Sign In</SidebarButtonRouter>}
                </SidebarButton>
            </SideBarWrapper>
        </SidebarContainer>
    );
}

export default SidebarUser
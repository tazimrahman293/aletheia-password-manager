import React from 'react'
import { SidebarContainer, Icon, CrossIcon, SideBarWrapper, SidebarMenu, SidebarButton, SidebarButtonRouter, SidebarLinkRouter} from './../Sidebar/SidebarElements'

/**
 * 
 * @param {isOpen, toggle} function used to keep track of clickEvents on Sidebar and HomeButton
 * @returns SidebarUser
 */
const SidebarUser = ({isOpen, toggle}) => {


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
                    <SidebarLinkRouter to='/settings' id='settings'>Settings</SidebarLinkRouter>
                </SidebarMenu>
                <SidebarButton>
                    <SidebarButtonRouter to='/signin'> Sign In</SidebarButtonRouter>
                </SidebarButton>
            </SideBarWrapper>
        </SidebarContainer>
    );
}

export default SidebarUser
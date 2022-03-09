import React from 'react'
import { SidebarContainer, Icon, CrossIcon, SideBarWrapper, SidebarMenu, SidebarLink, SidebarButton, SidebarButtonRouter} from './SidebarElements'

const Sidebar = ({isOpen, toggle}) => {
    return (
        <SidebarContainer isOpen={isOpen} onClick={toggle}>
            <Icon onClick={toggle}>
                <CrossIcon />
            </Icon>
            <SideBarWrapper>
                <SidebarMenu>
                    <SidebarLink to="/" onClick={toggle}>Home</SidebarLink>
                    <SidebarLink to="about" onClick={toggle}>About</SidebarLink>
                    <SidebarLink to="features" onClick={toggle}>Features</SidebarLink>
                    <SidebarLink to="team" onClick={toggle}>Team</SidebarLink>
                </SidebarMenu>
                <SidebarButton>
                    <SidebarButtonRouter to='/signin'> Sign In</SidebarButtonRouter>
                </SidebarButton>
            </SideBarWrapper>
        </SidebarContainer>
    );
}

export default Sidebar
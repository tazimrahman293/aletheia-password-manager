import React from 'react'
import { SidebarContainer, Icon, CrossIcon, SideBarWrapper, SidebarMenu, SidebarLink, SidebarButton, SidebarButtonRouter} from './SidebarElements'
import { animateScroll as scroll } from 'react-scroll';

/**
 * 
 * @param {isOpen, toggle} function used to keep track of clickEvents on Sidebar and HomeButton
 * @returns Sidebar
 */
const Sidebar = ({isOpen, toggle}) => {

    /**
     * Function to scroll to top of window onClickEvent
     */
    const toggleHome = () => {
        scroll.scrollToTop()
        toggle()
    }

    return (
        <SidebarContainer isOpen={isOpen} onClick={toggle}>
            <Icon onClick={toggle}>
                <CrossIcon />
            </Icon>
            <SideBarWrapper>
                <SidebarMenu>
                    <SidebarLink to="/" onClick={toggleHome} smooth={true} duration={500} spy={true} exact='true' offset={-80} >Home</SidebarLink>
                    <SidebarLink to="about" onClick={toggle} smooth={true} duration={500} spy={true} exact='true' offset={-80} >About</SidebarLink>
                    <SidebarLink to="features" onClick={toggle} smooth={true} duration={500} spy={true} exact='true' offset={-80} >Features</SidebarLink>
                    <SidebarLink to="team" onClick={toggle}  smooth={true} duration={500} spy={true} exact='true' offset={-80} >Team</SidebarLink>
                </SidebarMenu>
                <SidebarButton>
                    <SidebarButtonRouter to='/signin'> Sign In</SidebarButtonRouter>
                </SidebarButton>
            </SideBarWrapper>
        </SidebarContainer>
    );
}

export default Sidebar